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
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Mesh")
  USkeletalMeshComponent* WeaponMesh;

  /**Начала построения траектории стрельбы*/
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  FName MuzzleSocketName = "MuzzleSocket";

  /**Максимальная дистанция стрельбы, 1500 юнитов = 15 м*/
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  float TraceMaxDistance = 1500.0f;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  float DamageAmount = 10.0f;

  APlayerController* GetPlayerController() const;
  
  virtual void BeginPlay() override;
  virtual void MakeShot();
  virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
  
  void MakeDamage(const FHitResult& HitResult);
  bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
  FVector GetMuzzleWorldLocation() const;
  void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
};
