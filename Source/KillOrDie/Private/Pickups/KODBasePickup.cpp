// Kill or Die

#include "Pickups/KODBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

AKODBasePickup::AKODBasePickup() {
  PrimaryActorTick.bCanEverTick = true;
  CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
  CollisionComponent->InitSphereRadius(50.0f);
  CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
  SetRootComponent(CollisionComponent);
}
void AKODBasePickup::BeginPlay() {
  Super::BeginPlay();

}

void AKODBasePickup::NotifyActorBeginOverlap(AActor* OtherActor) {
  Super::NotifyActorBeginOverlap(OtherActor);
  Destroy(); 
}

void AKODBasePickup::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}
