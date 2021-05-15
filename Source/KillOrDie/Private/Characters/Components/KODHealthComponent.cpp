// Kill or Die

#include "Characters/Components/KODHealthComponent.h"

#include "Damage/KODFireDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UKODHealthComponent::UKODHealthComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

bool UKODHealthComponent::TryToAddHealthCond(float PickupHealAmount) {
  if(IsDead() || IsHealthFull) return false;
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
  if(ComponentOwner) ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UKODHealthComponent::OnTakeAnyDamage);
}

void UKODHealthComponent::OnTakeAnyDamage(AActor* DamagedActor,
    float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser) {
  if(Damage <= 0.0f || IsDead()) return;
  //отключаем таймер восстановления здоровья
  OnTimerRecoveryHealthEnd();
  
  //Проверяем что бы дамаг не выходил за указанные рамки
  SetHealth(Health - Damage);
  
  if(IsDead()) {
    //если умерли сообщаем всем подписантам что умерли
    OnDeath.Broadcast();
  } else if(AutoHeal && GetWorld()) {
    GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UKODHealthComponent::OnTimerRecoveryHealth, HealUpdateFrequency, true, HealDelay);
  }
}

void UKODHealthComponent::OnTimerRecoveryHealth() {
  SetHealth(Health + HealAmount);
  if(IsHealthFull() && GetWorld())
    OnTimerRecoveryHealthEnd();
}

void UKODHealthComponent::OnTimerRecoveryHealthEnd() {
  if(GetWorld()) 
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
}

void UKODHealthComponent::SetHealth(float NewHealth) {
  Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
  OnHealthChanged.Broadcast(Health);
}
