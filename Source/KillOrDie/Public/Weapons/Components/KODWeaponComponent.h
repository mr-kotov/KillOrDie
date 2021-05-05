// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KODWeaponComponent.generated.h"

class AKODBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData {
  GENERATED_BODY()
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  TSubclassOf<AKODBaseWeapon> WeaponClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  UAnimMontage* ReloadAnimMontage;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KILLORDIE_API UKODWeaponComponent : public UActorComponent {
  GENERATED_BODY()

public:
  UKODWeaponComponent();

  void StartFire();
  void StopFire();
  void NextWeapon();
  void Reload();

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
  TArray<FWeaponData> WeaponData;

  UPROPERTY(EditDefaultsOnly, Category="Weapon")
  FName WeaponEquipSocketName = "WeaponSocket";
  
  UPROPERTY(EditDefaultsOnly, Category="Weapon")
  FName WeaponArmorSocketName = "ArmorySocket";

  UPROPERTY(EditDefaultsOnly, Category="Animation")
  UAnimMontage* EquipAnimMontage;
  
  virtual void BeginPlay() override;
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
  UPROPERTY()
  AKODBaseWeapon* CurrentWeapon = nullptr;
  
  UPROPERTY()
  TArray<AKODBaseWeapon*> Weapons;  

  UPROPERTY()
  UAnimMontage* CurrentReloadAnimMontage = nullptr; 
  
  int32 CurrentWeaponIndex = 0;
  bool EquipAnimInProgress = false;
  bool ReloadAnimInProgress = false;
  
  void SpawnWeapons();
  void AttachWeaponToSocket(AKODBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName SocketName);
  void EquipWeapon(int32 WeaponIndex);
  void PlayAnimMontage(UAnimMontage* Animation);
  void InitAnimations();
  void OnEquipFinished(USkeletalMeshComponent* MeshComp);
  void OnReloadFinished(USkeletalMeshComponent* MeshComp);
  bool CanFire() const;
  bool CanEquip() const;
  bool CanReload() const;

  void OnEmptyClip();
  void ChangeClip();
  
  template<typename T> T* FindNotifyByClass(UAnimSequenceBase* Animation) {
    if(!Animation) return nullptr;
    const auto NotifyEvents = Animation->Notifies;
    for (auto NotifyEvent: NotifyEvents) {
      auto AnimNotify = Cast<T>(NotifyEvent.Notify);
      if(AnimNotify) {
        return AnimNotify;
      }
    }
    return nullptr;
  };
};
