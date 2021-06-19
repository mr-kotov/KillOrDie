// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Weapons/KODBaseWeapon.h"
#include "KODRifleWeapon.generated.h"

class UKODWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class KILLORDIE_API AKODRifleWeapon : public AKODBaseWeapon {
  GENERATED_BODY()

public:
  AKODRifleWeapon();
  
  virtual void StartFire() override;
  virtual void StopFire() override;

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  float TimerBetweenShots = 0.1f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  float BulletSpread = 1.5f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  float DamageAmount = 10.0f;
  
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
  UKODWeaponFXComponent* WeaponFXComponent;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  UNiagaraSystem* TraceFX;
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  FString TraceTargetName = "TraceTarget";

  virtual void BeginPlay() override;
  virtual void MakeShot() override;
  virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

  void MakeDamage(const FHitResult& HitResult);

private:
  FTimerHandle ShotTimerHandle;

  UPROPERTY()
  UNiagaraComponent* MuzzleFXComponent;

  UPROPERTY()
  UAudioComponent* FireAudioComponent;
  
  void InitFX();
  void SetFXActive(bool IsActive);
  void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
  AController* GetController() const;
};
