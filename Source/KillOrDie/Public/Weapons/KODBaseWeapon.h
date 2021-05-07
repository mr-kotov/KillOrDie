// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KODCoreTypes.h"
#include "KODBaseWeapon.generated.h"

class USkeletalMeshComponent;

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
  
  APlayerController* GetPlayerController() const;
  
  virtual void BeginPlay() override;
  virtual void MakeShot();
  virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
  
  
  bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
  FVector GetMuzzleWorldLocation() const;
  void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
  void DecreaseAmmo();
  bool IsAmmoEmpty() const;
  bool IsClipEmpty() const;
  void LogAmmo();
  
private:
  FAmmoData CurrentAmmo;  
};
