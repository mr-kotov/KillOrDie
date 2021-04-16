// Kill or Die

#include "Characters/Components/KODHealthComponent.h"

#include "Damage/KODFireDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UKODHealthComponent::UKODHealthComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UKODHealthComponent::BeginPlay() {
  Super::BeginPlay();
  
  Health = MaxHealth;
  OnHealthChanged.Broadcast(Health);
  AActor* ComponentOwner = GetOwner();
  if(ComponentOwner) {
    ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UKODHealthComponent::OnTakeAnyDamage); 
  }
}

void UKODHealthComponent::OnTakeAnyDamage(AActor* DamagedActor,
    float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser) {
  if(Damage <= 0.0f || IsDead()) return;

  //Проверяем что бы дамаг не выходил за указанные рамки
  Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
  OnHealthChanged.Broadcast(Health);
  
  if(IsDead()) {
    //если умерли сообщаем всем подписантам что умерли
    OnDeath.Broadcast();
  }
}
