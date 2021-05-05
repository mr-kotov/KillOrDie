#pragma once
#include "KODCoreTypes.generated.h"
//Weapon
class AKODBaseWeapon;

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

USTRUCT(BlueprintType)
struct FAmmoData {
  GENERATED_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  int32 Bullets;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", meta = (EditCondition = "!Infinite"))
  int32 Clips;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData {
  GENERATED_BODY()
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  TSubclassOf<AKODBaseWeapon> WeaponClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  UAnimMontage* ReloadAnimMontage;
};

//health
//оповещение умерли или нет
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);