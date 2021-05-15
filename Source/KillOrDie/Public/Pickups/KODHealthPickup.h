// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Pickups/KODBasePickup.h"
#include "KODHealthPickup.generated.h"

UCLASS()
class KILLORDIE_API AKODHealthPickup : public AKODBasePickup {
  GENERATED_BODY()

private:
  virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
