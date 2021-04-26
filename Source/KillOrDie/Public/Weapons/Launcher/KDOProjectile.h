// Kill or Die

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Actor.h"
#include "KDOProjectile.generated.h"

class USphereComponent;

UCLASS()
class KILLORDIE_API AKDOProjectile : public AActor {
  GENERATED_BODY()

public:
  AKDOProjectile();

protected:
  UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
  USphereComponent* CollisionComponent;
  
  virtual void BeginPlay() override;

};
