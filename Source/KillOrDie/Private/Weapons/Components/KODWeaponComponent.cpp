// Kill or Die

#include "Weapons/Components/KODWeaponComponent.h"

#include "KODBaseCharacter.h"
#include "KODEquipFinishedAnimNotify.h"
#include "Weapons/KODBaseWeapon.h"

UKODWeaponComponent::UKODWeaponComponent() {
  PrimaryComponentTick.bCanEverTick = false;
}

void UKODWeaponComponent::StartFire() {
  if(!CanFire()) return;
  
  CurrentWeapon->StartFire();
}

void UKODWeaponComponent::StopFire() {
  if(!CurrentWeapon) return;
  CurrentWeapon->StopFire();
}

void UKODWeaponComponent::NextWeapon() {
  if(!CanEquip()) return;
  
  CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
  EquipWeapon(CurrentWeaponIndex);
}

void UKODWeaponComponent::Reload() {
  PlayAnimMontage(CurrentReloadAnimMontage);
}

void UKODWeaponComponent::BeginPlay() {
  Super::BeginPlay();
  InitAnimations();
  SpawnWeapons();
  EquipWeapon(CurrentWeaponIndex);
}

void UKODWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
  CurrentWeapon = nullptr;
  for (auto Weapon : Weapons) {
    Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    Weapon->Destroy();
  }
  Weapons.Empty();
  Super::EndPlay(EndPlayReason);
}

void UKODWeaponComponent::SpawnWeapons() {  
  ACharacter* Character = Cast<AKODBaseCharacter>(GetOwner());
  if(!Character && !GetWorld()) return;

  for (auto OneWeaponData : WeaponData) {
    auto Weapon = GetWorld()->SpawnActor<AKODBaseWeapon>(OneWeaponData.WeaponClass);
    if(!Weapon) continue;

    Weapon->SetOwner(Character);
    Weapons.Add(Weapon);

    AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorSocketName);
  }
}

void UKODWeaponComponent::AttachWeaponToSocket(AKODBaseWeapon* Weapon,
    USceneComponent* SceneComponent, const FName SocketName) {
  if(!Weapon && !SceneComponent) return;
  
  FAttachmentTransformRules AttachmrntRules(EAttachmentRule::SnapToTarget, false);
  Weapon->AttachToComponent( SceneComponent, AttachmrntRules, SocketName);
}

void UKODWeaponComponent::EquipWeapon(int32 WeaponIndex) {
  if(WeaponIndex < 0 || WeaponIndex >= Weapons.Num()) return;
  
  ACharacter* Character = Cast<AKODBaseCharacter>(GetOwner());
  if(!Character && !GetWorld()) return;

  if(CurrentWeapon) {
    CurrentWeapon->StopFire();
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorSocketName);
  }
  
  CurrentWeapon = Weapons[WeaponIndex];
  //CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
  //лямбда функция для поиска нужного класса 
  const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {
    return Data.WeaponClass == CurrentWeapon->GetClass();
  });
  CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
  AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
  EquipAnimInProgress = true;
  PlayAnimMontage(EquipAnimMontage);
}

void UKODWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) {
  ACharacter* Character = Cast<AKODBaseCharacter>(GetOwner());
  if(!Character) return;

  Character->PlayAnimMontage(Animation);
}

void UKODWeaponComponent::InitAnimations() {
  if(!EquipAnimMontage) return;
  
  const auto NotifyEvents = EquipAnimMontage->Notifies;
  for (auto NotifyEvent: NotifyEvents) {
    UE_LOG(LogTemp, Warning, TEXT("InitAnimations"));
    auto EquipFinishedNotify = Cast<UKODEquipFinishedAnimNotify>(NotifyEvent.Notify);
    if(EquipFinishedNotify) {
      
      EquipFinishedNotify->OnNotified.AddUObject(this, &UKODWeaponComponent::OnEquipFinished);
      break;
    }
  }
}

void UKODWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp) {
  ACharacter* Character = Cast<AKODBaseCharacter>(GetOwner());
  if(!Character || Character->GetMesh() != MeshComp) return;

  EquipAnimInProgress = false;
}

bool UKODWeaponComponent::CanFire() const {
  return CurrentWeapon && !EquipAnimInProgress;
}

bool UKODWeaponComponent::CanEquip() const {
  return !EquipAnimInProgress;
}
