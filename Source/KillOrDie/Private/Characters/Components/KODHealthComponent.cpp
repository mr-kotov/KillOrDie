// Kill or Die

#include "Characters/Components/KODHealthComponent.h"

UKODHealthComponent::UKODHealthComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UKODHealthComponent::BeginPlay() {
  Super::BeginPlay();
  
  Health = MaxHealth;
}
