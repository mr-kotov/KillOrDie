// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KODWeaponComponent.generated.h"

class AKODBaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KILLORDIE_API UKODWeaponComponent : public UActorComponent {
  GENERATED_BODY()

public:
  UKODWeaponComponent();

  void Fire();

protected:
  UPROPERTY(EditDefaultsOnly, Category="WeaponComponent")
  TSubclassOf<AKODBaseWeapon> WeaponClass;

  UPROPERTY(EditDefaultsOnly, Category="WeaponComponent")
  FName WeaponAttachPointName = "WeaponSocket";
  

  virtual void BeginPlay() override;

private:
  UPROPERTY()
  AKODBaseWeapon* CurrentWeapon = nullptr;
  
  void SpawnWeapon();  
};
