// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "KODBaseWeapon.h"
#include "Components/ActorComponent.h"
#include "KODCoreTypes.h"
#include "KODWeaponComponent.generated.h"

class AKODBaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KILLORDIE_API UKODWeaponComponent : public UActorComponent {
  GENERATED_BODY()

public:
  UKODWeaponComponent();

  virtual void StartFire();
  virtual void StopFire();
  virtual void NextWeapon();
  void Reload();

  bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
  bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

  bool TryToAddAmmo(TSubclassOf<AKODBaseWeapon> WeaponType, int32 ClipsAmount);

  bool NeedAmmo(TSubclassOf<AKODBaseWeapon> WeaponType);
  
protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  TArray<FWeaponData> WeaponData;

  UPROPERTY(EditDefaultsOnly, Category="Weapon")
  FName WeaponEquipSocketName = "WeaponSocket";
  
  UPROPERTY(EditDefaultsOnly, Category="Weapon")
  FName WeaponArmorSocketName = "ArmorySocket";

  UPROPERTY(EditDefaultsOnly, Category="Animation")
  UAnimMontage* EquipAnimMontage;

  UPROPERTY()
  AKODBaseWeapon* CurrentWeapon = nullptr;
  
  UPROPERTY()
  TArray<AKODBaseWeapon*> Weapons;
  
  virtual void BeginPlay() override;
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  bool CanFire() const;
  bool CanEquip() const;
  void EquipWeapon(int32 WeaponIndex);
  int32 CurrentWeaponIndex = 0;

private:
  UPROPERTY()
  UAnimMontage* CurrentReloadAnimMontage = nullptr; 
  
  bool EquipAnimInProgress = false;
  bool ReloadAnimInProgress = false;
  
  void SpawnWeapons();
  void AttachWeaponToSocket(AKODBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName SocketName);
  void PlayAnimMontage(UAnimMontage* Animation);
  void InitAnimations();
  void OnEquipFinished(USkeletalMeshComponent* MeshComp);
  void OnReloadFinished(USkeletalMeshComponent* MeshComp);
  
  bool CanReload() const;

  void OnEmptyClip(AKODBaseWeapon* AmmoEmptyWeapon);
  void ChangeClip();
};
