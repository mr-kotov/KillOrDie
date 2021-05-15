// Kill or Die

#pragma once

#include "CoreMinimal.h"


#include "Pickups/KODBasePickup.h"
#include "KODAmmoPickup.generated.h"

class AKODBaseWeapon;

UCLASS()
class KILLORDIE_API AKODAmmoPickup : public AKODBasePickup {
  GENERATED_BODY()

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
  int32 ClipsAmount = 10;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
  TSubclassOf<AKODBaseWeapon> WeaponType;
  
private:
  virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
