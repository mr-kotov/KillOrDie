// Kill or Die

#include "Weapons/Launcher/KDOProjectile.h"
#include "Components/SphereComponent.h"

AKDOProjectile::AKDOProjectile() {
  PrimaryActorTick.bCanEverTick = false;
  CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
  CollisionComponent->InitSphereRadius(5.0f);
  SetRootComponent(CollisionComponent);
}

void AKDOProjectile::BeginPlay() {
  Super::BeginPlay();

}
