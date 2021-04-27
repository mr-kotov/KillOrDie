// Kill or Die

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Actor.h"
#include "KDOProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class KILLORDIE_API AKDOProjectile : public AActor {
  GENERATED_BODY()

public:
  AKDOProjectile();

  void SetShotDirection(const FVector& Direction){ShotDirection = Direction;};
protected:
  UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
  USphereComponent* CollisionComponent;

  UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
  UProjectileMovementComponent* MovementComponent;

  UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
  float DamageRadius = 200.0f;

  UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
  float DamageAmount = 50.0f;
  
  UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
  bool DoFullDamage = false;

  UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
  float LifeSeconds = 5.0f;
  
  virtual void BeginPlay() override;

private:
  FVector ShotDirection;

  UFUNCTION()
  void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

  AController* GetController() const;
};
