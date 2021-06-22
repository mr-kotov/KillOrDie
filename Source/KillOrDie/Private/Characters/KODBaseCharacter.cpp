// Kill or Die

#include "Characters/KODBaseCharacter.h"

#include "KODBaseWeapon.h"
#include "Characters/Components/KODCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Components/KODHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/KODWeaponComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

//SetDefaultSubobjectClass шаблонная функция принимает в качестве параметра шаблон класса подобъекта которым мы хотим заменить, в данном сулчае UKODCharacterMovementComponent
//в качестве параметра принимается наименование компонента 
AKODBaseCharacter::AKODBaseCharacter(const FObjectInitializer& ObjInitializer)
  : Super(
      ObjInitializer.SetDefaultSubobjectClass<UKODCharacterMovementComponent>(
          ACharacter::CharacterMovementComponentName)) {
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  HealthComponent = CreateDefaultSubobject<UKODHealthComponent>(
      "HealthComponent");

  WeaponComponent = CreateDefaultSubobject<UKODWeaponComponent>(
      "WeaponComponent");
}

void AKODBaseCharacter::BeginPlay() {
  Super::BeginPlay();
  //проверяем создание данных компонентов, работает только в сборках дебага, в релиз не идет
  check(HealthComponent);
  check(GetCharacterMovement());
  check(GetMesh());

  OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
  HealthComponent->OnDeath.AddUObject(this, &AKODBaseCharacter::OnDeath);
  HealthComponent->OnHealthChanged.AddUObject(
      this, &AKODBaseCharacter::OnHealthChanged);

  LandedDelegate.AddDynamic(this, &AKODBaseCharacter::OnGroundLanded);
}

void AKODBaseCharacter::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
}

bool AKODBaseCharacter::IsRunning() const {
  return false;
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

void AKODBaseCharacter::SetPlayerColor(const FLinearColor& Color) {
  const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
  if(!MaterialInst) return;

  MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}

void AKODBaseCharacter::OnDeath() {
  UE_LOG(LogBaseCharacter, Warning, TEXT("Player %s is dead"), *GetName());

  //PlayAnimMontage(DeathAnimMontage);
  GetCharacterMovement()->DisableMovement();
  SetLifeSpan(LifeSpanOnDeath);
  GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
  WeaponComponent->StopFire();
  WeaponComponent->Zoom(false);

  GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  GetMesh()->SetSimulatePhysics(true);

  UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void AKODBaseCharacter::OnHealthChanged(float Health, float HealthDelta) {
}

void AKODBaseCharacter::OnGroundLanded(const FHitResult& Hit) {
  const auto FallVelocityZ = -GetVelocity().Z;

  UE_LOG(LogBaseCharacter, Warning, TEXT("Velocity %f, LandedDamageVelocity: %f"), FallVelocityZ, LandedDamageVelocity.X);
  if (FallVelocityZ < LandedDamageVelocity.X) return;
  const auto FineDamage = FMath::GetMappedRangeValueClamped(
      LandedDamageVelocity, LandedDamage, FallVelocityZ);
  TakeDamage(FineDamage, FDamageEvent{}, nullptr, nullptr);
}
