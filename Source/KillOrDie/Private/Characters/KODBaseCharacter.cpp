// Kill or Die

#include "Characters/KODBaseCharacter.h"

#include "KODBaseWeapon.h"
#include "Camera/CameraComponent.h"
#include "Characters/Components/KODCharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Components/KODHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/KODWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

//SetDefaultSubobjectClass шаблонная функция принимает в качестве параметра шаблон класса подобъекта которым мы хотим заменить, в данном сулчае UKODCharacterMovementComponent
//в качестве параметра принимается наименование компонента 
AKODBaseCharacter::AKODBaseCharacter(const FObjectInitializer& ObjInitializer)
  : Super(
      ObjInitializer.SetDefaultSubobjectClass<UKODCharacterMovementComponent>(
          ACharacter::CharacterMovementComponentName)) {
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(
      "SpringArmComponent");
  SpringArmComponent->SetupAttachment(GetRootComponent());
  SpringArmComponent->bUsePawnControlRotation = true;
  SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

  CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
  CameraComponent->SetupAttachment(SpringArmComponent);

  HealthComponent = CreateDefaultSubobject<UKODHealthComponent>(
      "HealthComponent");

  HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>(
      "HealthTextComponent");
  HealthTextComponent->SetupAttachment(GetRootComponent());
  HealthTextComponent->SetOwnerNoSee(true);

  WeaponComponent = CreateDefaultSubobject<UKODWeaponComponent>(
      "WeaponComponent");
}

void AKODBaseCharacter::BeginPlay() {
  Super::BeginPlay();
  //проверяем создание данных компонентов, работает только в сборках дебага, в релиз не идет
  check(HealthComponent);
  check(HealthTextComponent);
  check(GetCharacterMovement());
  check(GetMesh());

  OnHealthChanged(HealthComponent->GetHealth());
  HealthComponent->OnDeath.AddUObject(this, &AKODBaseCharacter::OnDeath);
  HealthComponent->OnHealthChanged.AddUObject(
      this, &AKODBaseCharacter::OnHealthChanged);

  LandedDelegate.AddDynamic(this, &AKODBaseCharacter::OnGroundLanded);

}

void AKODBaseCharacter::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}

void AKODBaseCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  check(PlayerInputComponent);
  check(WeaponComponent);

  PlayerInputComponent->BindAxis("MoveForward", this, &AKODBaseCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this, &AKODBaseCharacter::MoveRight);
  PlayerInputComponent->BindAxis("LookUp", this, &AKODBaseCharacter::LookUp);
  PlayerInputComponent->BindAxis("TurnAround", this, &AKODBaseCharacter::TurnAround);
  PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKODBaseCharacter::Jump);
  PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AKODBaseCharacter::OnStartRunning);
  PlayerInputComponent->BindAction("Run", IE_Released, this, &AKODBaseCharacter::OnStopRunning);
  PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UKODWeaponComponent::StartFire);
  PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UKODWeaponComponent::StopFire);
  PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UKODWeaponComponent::NextWeapon);
  PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UKODWeaponComponent::Reload);
}

bool AKODBaseCharacter::IsRunning() const {
  return IsMovingForward && WantsToRun && !GetVelocity().IsZero();
}

float AKODBaseCharacter::GetMovementDirection() const {
  if (GetVelocity().IsZero()) return 0.0f;
  //получаем нормаль нашего вектора скорости
  const auto VelocityNormal = GetVelocity().GetSafeNormal();
  //высчитываем скаларное произведение вектора направления и вектора нормали, берем Acos от данного скалярного произв и получаем угол между векторами
  const auto AngleBetween = FMath::Acos(
      FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
  //получаем ортогональный вектор
  const auto CrossProduct = FVector::CrossProduct(
      GetActorForwardVector(), VelocityNormal);
  //преобразуем радианы в градусы
  const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
  return CrossProduct.IsZero()
           ? Degrees
           : Degrees * FMath::Sign(CrossProduct.Z);
  //домножаем на знак координаты Z
}

void AKODBaseCharacter::MoveForward(float Amount) {
  IsMovingForward = Amount > 0.0f;
  if (Amount == 0.0f) return;
  AddMovementInput(GetActorForwardVector(), Amount);
}

void AKODBaseCharacter::MoveRight(float Amount) {
  if (Amount == 0.0f) return;
  AddMovementInput(GetActorRightVector(), Amount);
}

void AKODBaseCharacter::LookUp(float Amount) {
  AddControllerPitchInput(Amount);
}

void AKODBaseCharacter::TurnAround(float Amount) {
  AddControllerYawInput(Amount);
}

void AKODBaseCharacter::OnStartRunning() {
  WantsToRun = true;
}

void AKODBaseCharacter::OnStopRunning() {
  WantsToRun = false;
}

void AKODBaseCharacter::OnDeath() {
  UE_LOG(LogBaseCharacter, Warning, TEXT("Player %s is dead"), *GetName());

  //PlayAnimMontage(DeathAnimMontage);
  GetCharacterMovement()->DisableMovement();
  SetLifeSpan(LifeSpanOnDeath);
  if (Controller) {
    Controller->ChangeState(NAME_Spectating);
  }
  GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
  HealthTextComponent->SetVisibility(false);
  WeaponComponent->StopFire();

  GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  GetMesh()->SetSimulatePhysics(true);
}

void AKODBaseCharacter::OnHealthChanged(float Health) {
  HealthTextComponent->SetText(
      FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void AKODBaseCharacter::OnGroundLanded(const FHitResult& Hit) {
  const auto FallVelocityZ = -GetVelocity().Z;
  if (FallVelocityZ < LandedDamageVelocity.X) return;
  const auto FineDamage = FMath::GetMappedRangeValueClamped(
      LandedDamageVelocity, LandedDamage, FallVelocityZ);
  TakeDamage(FineDamage, FDamageEvent{}, nullptr, nullptr);
}
