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
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  float TimerBetweenShots = 0.1f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  float BulletSpread = 1.5f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  float DamageAmount = 10.0f;
  
  virtual void MakeShot() override;
  virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

  void MakeDamage(const FHitResult& HitResult);

private:
  FTimerHandle ShotTimerHandle;
};
