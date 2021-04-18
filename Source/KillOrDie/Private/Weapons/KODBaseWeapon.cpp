// Kill or Die

#include "Weapons/KODBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

AKODBaseWeapon::AKODBaseWeapon() {
  PrimaryActorTick.bCanEverTick = false;
  WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
  SetRootComponent(WeaponMesh);
}

void AKODBaseWeapon::BeginPlay() {
  Super::BeginPlay();

}
