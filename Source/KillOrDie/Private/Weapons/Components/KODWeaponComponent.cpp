// Kill or Die

#include "Weapons/Components/KODWeaponComponent.h"

#include "KODBaseCharacter.h"
#include "Weapons/KODBaseWeapon.h"

UKODWeaponComponent::UKODWeaponComponent() {
  PrimaryComponentTick.bCanEverTick = false;
}

void UKODWeaponComponent::StartFire() {
  if(!CurrentWeapon) return;
  CurrentWeapon->StartFire();
}

void UKODWeaponComponent::StopFire() {
  if(!CurrentWeapon) return;
  CurrentWeapon->StopFire();
}

void UKODWeaponComponent::NextWeapon() {
  CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
  EquipWeapon(CurrentWeaponIndex);
}

void UKODWeaponComponent::BeginPlay() {
  Super::BeginPlay();
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

  for (auto WeaponClass : WeaponClasses) {
    auto Weapon = GetWorld()->SpawnActor<AKODBaseWeapon>(WeaponClass);
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
  ACharacter* Character = Cast<AKODBaseCharacter>(GetOwner());
  if(!Character && !GetWorld()) return;

  if(CurrentWeapon) {
    CurrentWeapon->StopFire();
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorSocketName);
  }
  
  CurrentWeapon = Weapons[WeaponIndex];
  AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
}
