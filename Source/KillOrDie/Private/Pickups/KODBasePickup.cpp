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
  check(CollisionComponent);
}

void AKODBasePickup::NotifyActorBeginOverlap(AActor* OtherActor) {
  Super::NotifyActorBeginOverlap(OtherActor);

  const auto Pawn = Cast<APawn>(OtherActor);
  if(GivePickupTo(Pawn)) {
    PickupWasTaken();  
  }
}

void AKODBasePickup::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}

bool AKODBasePickup::CouldBeTaken() const {
  return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

bool AKODBasePickup::GivePickupTo(APawn* PlayerPawn) {
  return false;
}

void AKODBasePickup::PickupWasTaken() {
  CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
  if(GetRootComponent()) {
    GetRootComponent()->SetVisibility(false, true);  
  }
  GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AKODBasePickup::Respawn, RespawnTime);
}

void AKODBasePickup::Respawn() {
  CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
  if(GetRootComponent()) {
    GetRootComponent()->SetVisibility(true, true);  
  }
}
