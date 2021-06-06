// Kill or Die

#include "Player/KODPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/KODWeaponComponent.h"

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

void AKODPlayerCharacter::OnDeath() {
  Super::OnDeath();
  if (Controller) {
    Controller->ChangeState(NAME_Spectating);
  }
}