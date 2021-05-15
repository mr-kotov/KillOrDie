// Kill or Die

#include "Pickups/KODAmmoPickup.h"
#include "KODHealthComponent.h"
#include "KODUtils.h"
#include "Components/KODWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AKODAmmoPickup::GivePickupTo(APawn* PlayerPawn) {
  const auto HealthComponent = KODUtils::GetKODPlayerComponent<UKODHealthComponent>(PlayerPawn);
  if(!HealthComponent || HealthComponent->IsDead()) return false;

  const auto WeaponComponent = KODUtils::GetKODPlayerComponent<UKODWeaponComponent>(PlayerPawn);
  if(!WeaponComponent) return false;

  return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
