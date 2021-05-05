// Kill or Die

#include "Weapons/KODBaseWeapon.h"
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
  CurrentAmmo = DefaultAmmo;
}

void AKODBaseWeapon::MakeShot() {
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

void AKODBaseWeapon::DecreaseAmmo() {
  if(CurrentAmmo.Clips == 0) {
    return;
  }
  CurrentAmmo.Bullets--;
  LogAmmo();

  if(IsClipEmpty() && !IsAmmoEmpty()) {
    OnClipEmpty.Broadcast();
  }
}

bool AKODBaseWeapon::IsAmmoEmpty() const {
  return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool AKODBaseWeapon::IsClipEmpty() const {
  return CurrentAmmo.Bullets == 0;
}

void AKODBaseWeapon::ChangeClip() {
  
  if(!CurrentAmmo.Infinite) {
    if(CurrentAmmo.Clips == 0) {
      return;
    }
    CurrentAmmo.Clips--;
  }
  CurrentAmmo.Bullets = DefaultAmmo.Bullets;
  UE_LOG(LogBaseWeapon, Warning, TEXT("------CLips------"));
}

bool AKODBaseWeapon::CanRealod() const {
  return  CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

void AKODBaseWeapon::LogAmmo() {
  FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
  AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
  UE_LOG(LogBaseWeapon, Warning, TEXT("%s"), *AmmoInfo);
}

void AKODBaseWeapon::StartFire() {
}

void AKODBaseWeapon::StopFire() {
}
