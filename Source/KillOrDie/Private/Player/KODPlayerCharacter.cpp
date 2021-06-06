// Kill or Die

#include "Player/KODPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/KODWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

AKODPlayerCharacter::AKODPlayerCharacter(const FObjectInitializer& ObjInitializer)
  : Super(ObjInitializer) {
  PrimaryActorTick.bCanEverTick = true;

  SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(
      "SpringArmComponent");
  SpringArmComponent->SetupAttachment(GetRootComponent());
  SpringArmComponent->bUsePawnControlRotation = true;
  SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

  CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
  CameraComponent->SetupAttachment(SpringArmComponent);

  CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
  CameraCollisionComponent->SetupAttachment(CameraComponent);
  CameraCollisionComponent->SetSphereRadius(10.0f);
  CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
  CameraCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AKODPlayerCharacter::BeginPlay() {
  Super::BeginPlay();
  check(CameraCollisionComponent);
  CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AKODPlayerCharacter::OnCameraCollisionBeginOverlap);
  CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AKODPlayerCharacter::OnCameraCollisionEndOverlap);
}

void AKODPlayerCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  check(PlayerInputComponent);
  check(WeaponComponent);

  PlayerInputComponent->BindAxis("MoveForward", this, &AKODPlayerCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this, &AKODPlayerCharacter::MoveRight);
  PlayerInputComponent->BindAxis("LookUp", this, &AKODPlayerCharacter::LookUp);
  PlayerInputComponent->BindAxis("TurnAround", this, &AKODPlayerCharacter::TurnAround);
  PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKODPlayerCharacter::Jump);
  PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AKODPlayerCharacter::OnStartRunning);
  PlayerInputComponent->BindAction("Run", IE_Released, this, &AKODPlayerCharacter::OnStopRunning);
  PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UKODWeaponComponent::StartFire);
  PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UKODWeaponComponent::StopFire);
  PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UKODWeaponComponent::NextWeapon);
  PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UKODWeaponComponent::Reload);
}

bool AKODPlayerCharacter::IsRunning() const {
  return IsMovingForward && WantsToRun && !GetVelocity().IsZero();
}

void AKODPlayerCharacter::MoveForward(float Amount) {
  IsMovingForward = Amount > 0.0f;
  if (Amount == 0.0f) return;
  AddMovementInput(GetActorForwardVector(), Amount);
}

void AKODPlayerCharacter::MoveRight(float Amount) {
  if (Amount == 0.0f) return;
  AddMovementInput(GetActorRightVector(), Amount);
}

void AKODPlayerCharacter::LookUp(float Amount) {
  AddControllerPitchInput(Amount);
}

void AKODPlayerCharacter::TurnAround(float Amount) {
  AddControllerYawInput(Amount);
}

void AKODPlayerCharacter::OnStartRunning() {
  WantsToRun = true;
}

void AKODPlayerCharacter::OnStopRunning() {
  WantsToRun = false;
}

void AKODPlayerCharacter::OnCameraCollisionBeginOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult) {
  CheckCameraOverlap();
}

void AKODPlayerCharacter::OnCameraCollisionEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
  CheckCameraOverlap();
}

void AKODPlayerCharacter::CheckCameraOverlap() {
  const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
  GetMesh()->SetOwnerNoSee(HideMesh);

  TArray<USceneComponent*> MeshChildren; 
  GetMesh()->GetChildrenComponents(true, MeshChildren);

  for (auto MeshChild: MeshChildren) {
    const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
    if(MeshChildGeometry) {
      MeshChildGeometry->SetOwnerNoSee(HideMesh);
    }
  }
}

void AKODPlayerCharacter::OnDeath() {
  Super::OnDeath();
  if (Controller) {
    Controller->ChangeState(NAME_Spectating);
  }
}


