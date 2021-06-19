// Kill or Die

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Actor.h"
#include "KODBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class KILLORDIE_API AKODBasePickup : public AActor {
  GENERATED_BODY()

public:
  AKODBasePickup();

protected:

  UPROPERTY(VisibleAnywhere, Category = "Pickup")
  USphereComponent* CollisionComponent;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
  float RespawnTime = 5.0f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
  USoundCue* TakenSound;
  
  virtual void BeginPlay() override;
  virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
  virtual void Tick(float DeltaTime) override;
  bool CouldBeTaken() const;

private:
  FTimerHandle RespawnTimerHandle;
  
  virtual bool GivePickupTo(APawn* PlayerPawn);
  
  void PickupWasTaken();
  void Respawn();
};
