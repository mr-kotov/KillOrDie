// Kill or Die


#include "Characters/Components/KODCharacterMovementComponent.h"

#include "Characters/KODBaseCharacter.h"

float UKODCharacterMovementComponent::GetMaxSpeed() const {
  const float MaxSpeed = Super::GetMaxSpeed();
  const AKODBaseCharacter* Player = Cast<AKODBaseCharacter>(GetPawnOwner());
  return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
