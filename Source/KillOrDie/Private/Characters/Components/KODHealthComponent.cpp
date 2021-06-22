// Kill or Die

#include "Characters/Components/KODHealthComponent.h"
#include "GameFramework/Character.h"
#include "KODGameModeBase.h"
#include "Damage/KODFireDamageType.h"
#include "Perception/AISense_Damage.h"
#include "Player/KDOAIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UKODHealthComponent::UKODHealthComponent() {
  PrimaryComponentTick.bCanEverTick = false;
}

bool UKODHealthComponent::TryToAddHealthCond(float PickupHealAmount) {
  if (IsDead() || IsHealthFull()) return false;
  SetHealth(Health + PickupHealAmount);
  return true;
}

bool UKODHealthComponent::IsHealthFull() const {
  return FMath::IsNearlyEqual(Health, MaxHealth);
}

// Called when the game starts
void UKODHealthComponent::BeginPlay() {
  Super::BeginPlay();

  check(MaxHealth > 0);
  SetHealth(MaxHealth);
  AActor* ComponentOwner = GetOwner();
  if (ComponentOwner) {
    ComponentOwner->OnTakeAnyDamage.AddDynamic(
        this, &UKODHealthComponent::OnTakeAnyDamage);
    ComponentOwner->OnTakePointDamage.AddDynamic(
        this, &UKODHealthComponent::OnTakePointDamage);
    ComponentOwner->OnTakeRadialDamage.AddDynamic(
        this, &UKODHealthComponent::OnTakeRadialDamage);
  }
}

void UKODHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor,
    float Damage,
    const UDamageType* DamageType,
    AController* InstigatedBy,
    AActor* DamageCauser) {
  if(!InstigatedBy) {
    ApplyDamage(Damage, InstigatedBy); 
  }
}

void UKODHealthComponent::OnTakePointDamage(
    AActor* DamagedActor,
    float Damage,
    AController* InstigatedBy,
    FVector HitLocation,
    UPrimitiveComponent* FHitComponent,
    FName BoneName,
    FVector ShotFromDirection,
    const UDamageType* DamageType,
    AActor* DamageCauser) {
  const auto FinalDamage = Damage * GetPointDamageModifier(
                               DamagedActor, BoneName);
  UE_LOG(
      LogHealthComponent, Display,
      TEXT("On point damage: %f, final damage: %f, bone: %s"), Damage,
      FinalDamage, *BoneName.ToString());
  ApplyDamage(FinalDamage, InstigatedBy);
}

void UKODHealthComponent::OnTakeRadialDamage(
    AActor* DamagedActor,
    float Damage,
    const UDamageType* DamageType,
    FVector Origin,
    FHitResult HitInfo,
    AController* InstigatedBy,
    AActor* DamageCauser) {
  UE_LOG(LogHealthComponent, Display, TEXT("On radial damage: %f"), Damage);
  ApplyDamage(Damage, InstigatedBy);
}

void UKODHealthComponent::OnTimerRecoveryHealth() {
  SetHealth(Health + HealAmount);
  if (IsHealthFull() && GetWorld()) OnTimerRecoveryHealthEnd();
}

void UKODHealthComponent::OnTimerRecoveryHealthEnd() {
  if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
}

void UKODHealthComponent::SetHealth(float NewHealth) {
  const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
  const auto HealthDelta = NewHealth - Health;
  Health = NextHealth;
  OnHealthChanged.Broadcast(Health, HealthDelta);
}

void UKODHealthComponent::PlayCameraShake() {
  if (IsDead()) return;

  const auto Player = Cast<APawn>(GetOwner());
  if (!Player) return;

  const auto Controller = Player->GetController<APlayerController>();
  if (!Controller || !Controller->PlayerCameraManager) return;

  Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void UKODHealthComponent::Killed(AController* KillerController) {
  if (!GetWorld()) return;

  const auto GameMode = Cast<AKODGameModeBase>(GetWorld()->GetAuthGameMode());
  if (!GameMode) return;

  const auto Player = Cast<APawn>(GetOwner());
  const auto VictimController = Player ? Player->Controller : nullptr;

  GameMode->Killed(KillerController, VictimController);
}

void UKODHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy) {
  if (Damage <= 0.0f || IsDead()) return;
  //отключаем таймер восстановления здоровья
  OnTimerRecoveryHealthEnd();

  //Проверяем что бы дамаг не выходил за указанные рамки
  SetHealth(Health - Damage);

  if (IsDead()) {
    Killed(InstigatedBy);
    //если умерли сообщаем всем подписантам что умерли
    OnDeath.Broadcast();
  } else if (AutoHeal && GetWorld()) {
    GetWorld()->GetTimerManager().SetTimer(
        HealTimerHandle, this,
        &UKODHealthComponent::OnTimerRecoveryHealth,
        HealUpdateFrequency, true,
        HealDelay);
  }
  PlayCameraShake();
  ReportDamageEvent(Damage, InstigatedBy);
}

float UKODHealthComponent::GetPointDamageModifier(
    AActor* DamageActor,
    const FName& BoneName) {
  const auto Character = Cast<ACharacter>(DamageActor);
  if (!Character || !Character->GetMesh() || !Character->GetMesh()->
      GetBodyInstance(BoneName))
    return 1.0f;

  const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->
                                       GetSimplePhysicalMaterial();
  if (!PhysMaterial || !DamageModifiers.Contains(PhysMaterial)) return 1.0f;

  return DamageModifiers[PhysMaterial];
}

void UKODHealthComponent::ReportDamageEvent(
    float Damage,
    AController* InstigateBy) {
  if (!GetWorld() ||             //
      !InstigateBy || //
      !InstigateBy->GetPawn() || //
      !GetOwner())               //
    return;

  const auto Player = Cast<APawn>(GetOwner());
  if (!Player) return;

  const auto AIController = Player->GetController<AKDOAIController>();
  if(!AIController) return;
  
  UAISense_Damage::ReportDamageEvent(
      GetWorld(),                                 //
      GetOwner(),                                 //
      InstigateBy->GetPawn(),                     //
      Damage,                                     //
      InstigateBy->GetPawn()->GetActorLocation(), //
      GetOwner()->GetActorLocation());
}
