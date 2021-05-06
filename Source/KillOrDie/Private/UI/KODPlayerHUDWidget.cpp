// Kill or Die

#include "UI/KODPlayerHUDWidget.h"

#include "Characters/Components/KODHealthComponent.h"

float UKODPlayerHUDWidget::GetHealthPercent() const {
  const auto Player = GetOwningPlayerPawn();
  if(!Player) return  0.0f;

  const auto Component = Player->GetComponentByClass(UKODHealthComponent::StaticClass());
  const auto HealthComponent = Cast<UKODHealthComponent>(Component);
  if(!HealthComponent) return 0.0f;

  return HealthComponent->GetHealthPercent();
}
