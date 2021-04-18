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

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  USkeletalMeshComponent* WeaponMesh;
  
  virtual void BeginPlay() override;


};
