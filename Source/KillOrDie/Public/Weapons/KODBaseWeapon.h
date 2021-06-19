// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KODCoreTypes.h"
#include "KODBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

UCLASS()
class KILLORDIE_API AKODBaseWeapon : public AActor {
  GENERATED_BODY()

public:
  AKODBaseWeapon();

  FOnClipEmptySignature OnClipEmpty;
  
  virtual void StartFire();
  virtual void StopFire();

  void ChangeClip();
  bool CanRealod() const;

  FWeaponUIData GetUIData() const {return UIData;}
  FAmmoData GetAmmoData() const {return CurrentAmmo;}

  bool TryToAddAmmo(int32 ClipsAmount);
  bool IsAmmoEmpty() const;
  bool IsAmmoFull() const;
  
protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
  USkeletalMeshComponent* WeaponMesh;

  /**Начала построения траектории стрельбы*/
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  FName MuzzleSocketName = "MuzzleSocket";

  /**Максимальная дистанция стрельбы, 1500 юнитов = 15 м*/
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  float TraceMaxDistance = 1500.0f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  FAmmoData DefaultAmmo {15, 10, false};

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
  FWeaponUIData UIData;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
  UNiagaraSystem* MuzzleFX;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
  USoundCue* FireSound;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
  USoundCue* NoAmmoSound;
   
  virtual void BeginPlay() override;
  virtual void MakeShot();
  virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
  
  
  bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
  FVector GetMuzzleWorldLocation() const;
  void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
  void DecreaseAmmo();
  
  bool IsClipEmpty() const;
  void LogAmmo();
  
  UNiagaraComponent* SpawnMuzzleFX();
private:
  FAmmoData CurrentAmmo;  
};
