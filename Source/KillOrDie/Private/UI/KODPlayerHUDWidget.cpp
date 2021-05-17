// Kill or Die

#include "UI/KODPlayerHUDWidget.h"
#include "Weapons/Components/KODWeaponComponent.h"
#include "KODUtils.h"
#include "Characters/Components/KODHealthComponent.h"

float UKODPlayerHUDWidget::GetHealthPercent() const {
  const auto HealthComponent = KODUtils::GetKODPlayerComponent<UKODHealthComponent>(GetOwningPlayerPawn());
  if(!HealthComponent) return 0.0f;

  return HealthComponent->GetHealthPercent();
}

bool UKODPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const {
  const auto WeaponComponent = KODUtils::GetKODPlayerComponent<UKODWeaponComponent>(GetOwningPlayerPawn());
  if(!WeaponComponent) return false;

  return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UKODPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const {
  const auto WeaponComponent = KODUtils::GetKODPlayerComponent<UKODWeaponComponent>(GetOwningPlayerPawn());
  if(!WeaponComponent) return false;

  return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool UKODPlayerHUDWidget::IsPlayerAlive() const {
  const auto HealthComponent = KODUtils::GetKODPlayerComponent<UKODHealthComponent>(GetOwningPlayerPawn());
  return HealthComponent && !HealthComponent->IsDead();
}

bool UKODPlayerHUDWidget::IsPlayerSpectating() const {
  const auto Controller = GetOwningPlayer();
  return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool UKODPlayerHUDWidget::Initialize() {
  const auto HealthComponent = KODUtils::GetKODPlayerComponent<UKODHealthComponent>(GetOwningPlayerPawn());
  if(HealthComponent) {
    HealthComponent->OnHealthChanged.AddUObject(this, &UKODPlayerHUDWidget::OnHealthChanged);
  }
  return Super::Initialize();
}

void UKODPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta) {
  if(HealthDelta < 0.0f) {
    OnTakeDamage();  
  }
}
