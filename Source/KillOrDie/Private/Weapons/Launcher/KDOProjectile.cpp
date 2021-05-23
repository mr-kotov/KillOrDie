// Kill or Die

#include "Weapons/Launcher/KDOProjectile.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Components/KODWeaponFXComponent.h"
#include "NiagaraComponent.h"

AKDOProjectile::AKDOProjectile() {
  PrimaryActorTick.bCanEverTick = false;
  CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
  CollisionComponent->InitSphereRadius(5.0f);
  CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
  CollisionComponent->bReturnMaterialOnMove = true;
  SetRootComponent(CollisionComponent);

  ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
  ProjectileMesh->SetupAttachment(RootComponent);
  
  EffectTraceSmokeComponent = CreateDefaultSubobject<UNiagaraComponent>("EffectTraceSmoke");
  EffectTraceSmokeComponent->SetupAttachment(RootComponent);
  
  EffectTraceComponent = CreateDefaultSubobject<UNiagaraComponent>("EffectTrace");
  EffectTraceComponent->SetupAttachment(RootComponent);  

   

  MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
  MovementComponent->InitialSpeed = 2000.0f;
  MovementComponent->ProjectileGravityScale = 0.0f;

  WeaponFXComponent = CreateDefaultSubobject<UKODWeaponFXComponent>("WeaponFXComponent");
}

void AKDOProjectile::BeginPlay() {
  Super::BeginPlay();

  check(MovementComponent);
  check(CollisionComponent);
  check(MovementComponent->ProjectileGravityScale == 0.0f);
  check(MovementComponent->InitialSpeed > 0.0f);
  check(WeaponFXComponent);
  
  MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
  CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
  CollisionComponent->OnComponentHit.AddDynamic(this, &AKDOProjectile::OnProjectileHit);

  /**Самоликвидация через 5 сек*/
  SetLifeSpan(LifeSeconds);
}

void AKDOProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
    const FHitResult& Hit) {
  if(!GetWorld()) return;

  MovementComponent->StopMovementImmediately();
  //make damage
  UGameplayStatics::ApplyRadialDamage(GetWorld(),//
    DamageAmount,//
    GetActorLocation(),//
    DamageRadius,//
    UDamageType::StaticClass(),//
    {GetOwner()},//
    this,//
    GetController(),//
    DoFullDamage);

  //DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);
  WeaponFXComponent->PlayImpactFX(Hit);
  //SetActorHiddenInGame(true);
  SetActorEnableCollision(false);
  EffectTraceComponent->SetVisibility(false);
  ProjectileMesh->SetVisibility(false);
  //Destroy();
}

AController* AKDOProjectile::GetController() const {
  const auto Pawn = Cast<APawn>(GetOwner());
  return Pawn ? Pawn->GetController() : nullptr;
}
