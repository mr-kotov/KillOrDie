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

void UKODWeaponComponent::BeginPlay() {
  Super::BeginPlay();
  SpawnWeapon();
}

void UKODWeaponComponent::SpawnWeapon() {
  if(!GetWorld()) return;
  
  ACharacter* Character = Cast<AKODBaseCharacter>(GetOwner());
  if(!Character) return;

  CurrentWeapon = GetWorld()->SpawnActor<AKODBaseWeapon>(WeaponClass);
  if(!CurrentWeapon) return;
  
  FAttachmentTransformRules AttachmrntRules(EAttachmentRule::SnapToTarget, false);
  CurrentWeapon->AttachToComponent( Character->GetMesh(), AttachmrntRules, WeaponAttachPointName);
  CurrentWeapon->SetOwner(Character);
}
