// Kill or Die

#include "Pickups/KODHealthPickup.h"
DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AKODHealthPickup::GivePickupTo(APawn* PlayerPawn) {
  return true;
}
