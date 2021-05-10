// Kill or Die

#include "UI/KODPlayerHUDWidget.h"
#include "Weapons/Components/KODWeaponComponent.h"
#include "Characters/Components/KODHealthComponent.h"

float UKODPlayerHUDWidget::GetHealthPercent() const {
  const auto HealthComponent = GetHealthComponent();
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

bool UKODPlayerHUDWidget::IsPlayerAlive() const {
  const auto HealthComponent = GetHealthComponent();
  return HealthComponent && !HealthComponent->IsDead();
}

bool UKODPlayerHUDWidget::IsPlayerSpectating() const {
  const auto Controller = GetOwningPlayer();
  return Controller && Controller->GetStateName() == NAME_Spectating;
}

UKODWeaponComponent* UKODPlayerHUDWidget::GetWeaponComponent() const {
  const auto Player = GetOwningPlayerPawn();
  if(!Player) return nullptr;

  const auto Component = Player->GetComponentByClass(UKODWeaponComponent::StaticClass());
  const auto WeaponComponent = Cast<UKODWeaponComponent>(Component);
  return WeaponComponent;
}

UKODHealthComponent* UKODPlayerHUDWidget::GetHealthComponent() const {
  const auto Player = GetOwningPlayerPawn();
  if(!Player) return nullptr;

  const auto Component = Player->GetComponentByClass(UKODHealthComponent::StaticClass());
  const auto HealthComponent = Cast<UKODHealthComponent>(Component);
  return HealthComponent;
}
