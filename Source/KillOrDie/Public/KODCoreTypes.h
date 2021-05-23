#pragma once
#include "KODCoreTypes.generated.h"
//Weapon
class AKODBaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, AKODBaseWeapon*);

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

USTRUCT(BlueprintType)
struct FWeaponUIData {
  GENERATED_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
  UTexture2D* MainIcon;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  UTexture2D* CrossHairIcon;
};

//health
//оповещение умерли или нет
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);

/**VFX*/
class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FDecalData {
  GENERATED_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
  UMaterialInterface* Material;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
  FVector Size = FVector(10.0f);
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
  float LiftTime = 5.0f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
  float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData {
  GENERATED_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
  UNiagaraSystem* NiagaraEffect;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
  FDecalData DecalData;
};

