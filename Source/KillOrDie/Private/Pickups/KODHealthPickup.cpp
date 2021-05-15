// Kill or Die

#include "Pickups/KODHealthPickup.h"
#include "KODUtils.h"
#include "Characters/Components/KODHealthComponent.h"
DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AKODHealthPickup::GivePickupTo(APawn* PlayerPawn) {
  const auto HealthComponent = KODUtils::GetKODPlayerComponent<UKODHealthComponent>(PlayerPawn);
  if(!HealthComponent || HealthComponent->IsDead()) return false;

  return HealthComponent->TryToAddHealthCond(HealAmount);
}
