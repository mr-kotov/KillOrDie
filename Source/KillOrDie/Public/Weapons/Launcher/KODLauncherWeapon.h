// Kill or Die

#pragma once

#include "CoreMinimal.h"


#include "Weapons/KODBaseWeapon.h"
#include "KODLauncherWeapon.generated.h"

class AKDOProjectile;

UCLASS()
class KILLORDIE_API AKODLauncherWeapon : public AKODBaseWeapon {
  GENERATED_BODY()

public:
  virtual void StartFire() override;

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  TSubclassOf<AKDOProjectile> ProjectileClass;
  
  virtual void MakeShot() override;
};
