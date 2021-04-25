// Kill or Die

#include "Weapons/KODBaseWeapon.h"

#include "DrawDebugHelpers.h"
#include "KODBaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

AKODBaseWeapon::AKODBaseWeapon() {
  PrimaryActorTick.bCanEverTick = false;
  WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
  SetRootComponent(WeaponMesh);
}

void AKODBaseWeapon::BeginPlay() {
  Super::BeginPlay();
  check(WeaponMesh);
}

void AKODBaseWeapon::MakeShot() {
  if(!GetWorld()) return;

  FVector TraceStart, TraceEnd;
  if(!GetTraceData(TraceStart, TraceEnd)) return;

  FHitResult HitResult;
  MakeHit(HitResult, TraceStart, TraceEnd);
  
  if(HitResult.bBlockingHit) {
    MakeDamage(HitResult);
    DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 1.0f, 0, 3.0f);
    DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 1.0f);
  } else {
    DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Blue, false, 3.0f, 0, 5.0f);
  }
}

void AKODBaseWeapon::MakeDamage(const FHitResult& HitResult) {
  const auto DamgeActor = HitResult.GetActor();
  if(!DamgeActor) return;
  DamgeActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}

APlayerController* AKODBaseWeapon::GetPlayerController() const {
  const auto Player = Cast<ACharacter>(GetOwner());
  if(!Player) nullptr;

  return Player->GetController<APlayerController>();
}

bool AKODBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const {
  const auto Controller = GetPlayerController();
  if(!Controller) return false;
  Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
  return true;
}

FVector AKODBaseWeapon::GetMuzzleWorldLocation() const {
  return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool AKODBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const {
  FVector ViewLocation;
  FRotator ViewRotation;
  if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
  
  /**Получаем положенее в мире, начало траектории*/
  TraceStart = ViewLocation;//SocketTransform.GetLocation();
  /**Получаем направление стрельбы*/
  const FVector ShootDirection = ViewRotation.Vector();//SocketTransform.GetRotation().GetForwardVector();
  /**Получаем последнюю точку для формирования траектории стрельбы*/
  TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
  return true;
}

void AKODBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart,
    const FVector& TraceEnd) {
  FCollisionQueryParams CollisionParams;
  CollisionParams.AddIgnoredActor(GetOwner());
  GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void AKODBaseWeapon::Fire() {
  MakeShot();
}
