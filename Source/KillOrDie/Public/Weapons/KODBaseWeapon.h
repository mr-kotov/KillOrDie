// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KODBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class KILLORDIE_API AKODBaseWeapon : public AActor {
  GENERATED_BODY()

public:
  AKODBaseWeapon();

  virtual void StartFire();
  virtual void StopFire();

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Mesh")
  USkeletalMeshComponent* WeaponMesh;

  /**Начала построения траектории стрельбы*/
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  FName MuzzleSocketName = "MuzzleSocket";

  /**Максимальная дистанция стрельбы, 1500 юнитов = 15 м*/
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  float TraceMaxDistance = 1500.0f;



  APlayerController* GetPlayerController() const;
  
  virtual void BeginPlay() override;
  virtual void MakeShot();
  virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
  
  
  bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
  FVector GetMuzzleWorldLocation() const;
  void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
};
