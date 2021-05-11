// Kill or Die

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Actor.h"
#include "KODBasePickup.generated.h"

class USphereComponent;

UCLASS()
class KILLORDIE_API AKODBasePickup : public AActor {
  GENERATED_BODY()

public:
  AKODBasePickup();

protected:

  UPROPERTY(VisibleAnywhere, Category = "Pickup")
  USphereComponent* CollisionComponent;
  
  virtual void BeginPlay() override;
  virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
  virtual void Tick(float DeltaTime) override;

};
