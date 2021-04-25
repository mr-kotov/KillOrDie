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

  virtual void Fire();
  
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
    
  virtual void BeginPlay() override;

  void MakeShot();
  void MakeDamage(const FHitResult& HitResult);

private:
  APlayerController* GetPlayerController() const;
  bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
  FVector GetMuzzleWorldLocation() const;
  bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
  void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
};
