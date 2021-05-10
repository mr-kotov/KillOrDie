// Kill or Die

#include "UI/KODPlayerHUDWidget.h"
#include "Weapons/Components/KODWeaponComponent.h"
#include "Characters/Components/KODHealthComponent.h"

float UKODPlayerHUDWidget::GetHealthPercent() const {
  const auto Player = GetOwningPlayerPawn();
  if(!Player) return  0.0f;

  const auto Component = Player->GetComponentByClass(UKODHealthComponent::StaticClass());
  const auto HealthComponent = Cast<UKODHealthComponent>(Component);
  if(!HealthComponent) return 0.0f;

  return HealthComponent->GetHealthPercent();
}

bool UKODPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const {
  const auto WeaponComponent = GetWeaponComponent();
  if(!WeaponComponent) return false;

  return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UKODPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const {
  const auto WeaponComponent = GetWeaponComponent();
  if(!WeaponComponent) return false;

  return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

UKODWeaponComponent* UKODPlayerHUDWidget::GetWeaponComponent() const {
  const auto Player = GetOwningPlayerPawn();
  if(!Player) return nullptr;

  const auto Component = Player->GetComponentByClass(UKODWeaponComponent::StaticClass());
  const auto WeaponComponent = Cast<UKODWeaponComponent>(Component);
  return WeaponComponent;
}