// Kill or Die

#include "Dev/Damage/KODDevDamageActor.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

AKODDevDamageActor::AKODDevDamageActor() {
  PrimaryActorTick.bCanEverTick = true;

  SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
  SetRootComponent(SceneComponent);
}

void AKODDevDamageActor::BeginPlay() {
  Super::BeginPlay();
}

void AKODDevDamageActor::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

  DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);

  UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(),
                                      Radius, DamageType, {}, this, nullptr,
                                      DoFullDamage);

}
