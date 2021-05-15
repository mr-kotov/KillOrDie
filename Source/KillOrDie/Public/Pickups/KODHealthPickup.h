// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Pickups/KODBasePickup.h"
#include "KODHealthPickup.generated.h"

UCLASS()
class KILLORDIE_API AKODHealthPickup : public AKODBasePickup {
  GENERATED_BODY()

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
  float HealAmount = 50.0f;
  
private:
  virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
