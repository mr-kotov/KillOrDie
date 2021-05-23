// Kill or Die

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Actor.h"
#include "KDOProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UKODWeaponFXComponent;
class UNiagaraComponent;

UCLASS()
class KILLORDIE_API AKDOProjectile : public AActor {
  GENERATED_BODY()

public:
  AKDOProjectile();

  void SetShotDirection(const FVector& Direction){ShotDirection = Direction;};
protected:
  UPROPERTY(VisibleDefaultsOnly, Category = "Components")
  USphereComponent* CollisionComponent;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
  UStaticMeshComponent* ProjectileMesh;
  
  UPROPERTY(VisibleDefaultsOnly, Category = "Components")
  UProjectileMovementComponent* MovementComponent;

  UPROPERTY(VisibleDefaultsOnly, Category = "VFX")
  UNiagaraComponent* EffectTraceComponent;

  UPROPERTY(VisibleDefaultsOnly, Category = "VFX")
  UNiagaraComponent* EffectTraceSmokeComponent;

  UPROPERTY(EditDefaultsOnly, Category = "Weapon")
  float DamageRadius = 200.0f;

  UPROPERTY(EditDefaultsOnly, Category = "Weapon")
  float DamageAmount = 50.0f;
  
  UPROPERTY(EditDefaultsOnly, Category = "Weapon")
  bool DoFullDamage = false;

  UPROPERTY(EditDefaultsOnly, Category = "Weapon")
  float LifeSeconds = 2.0f;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
  UKODWeaponFXComponent* WeaponFXComponent;
  
  virtual void BeginPlay() override;

private:
  FVector ShotDirection;

  UFUNCTION()
  void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

  AController* GetController() const;
};
