// Kill or Die

#include "Weapons/KODBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeaponComponent, All, All);

AKODBaseWeapon::AKODBaseWeapon() {
  PrimaryActorTick.bCanEverTick = false;
  WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
  SetRootComponent(WeaponMesh);
}

void AKODBaseWeapon::BeginPlay() {
  Super::BeginPlay();

}

void AKODBaseWeapon::Fire() {
 UE_LOG(LogBaseWeaponComponent, Warning, TEXT("Fire")); 
}
