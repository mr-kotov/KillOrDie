// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Weapons/KODBaseWeapon.h"
#include "KODRifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class KILLORDIE_API AKODRifleWeapon : public AKODBaseWeapon {
  GENERATED_BODY()

public:
  virtual void StartFire() override;
  virtual void StopFire() override;

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  float TimerBetweenShots = 0.1f;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  float BulletSpread = 1.5f;
  
  virtual void MakeShot() override;
  virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
  FTimerHandle ShotTimerHandle;
};
