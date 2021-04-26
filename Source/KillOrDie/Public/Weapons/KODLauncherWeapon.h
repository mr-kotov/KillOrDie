// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Weapons/KODBaseWeapon.h"
#include "KODLauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class KILLORDIE_API AKODLauncherWeapon : public AKODBaseWeapon {
  GENERATED_BODY()

public:
  virtual void StartFire() override;
  virtual void StopFire() override;

protected:
  virtual void MakeShot() override;
};
