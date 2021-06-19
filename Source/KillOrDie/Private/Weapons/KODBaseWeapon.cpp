// Kill or Die

#include "Weapons/KODBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

AKODBaseWeapon::AKODBaseWeapon() {
  PrimaryActorTick.bCanEverTick = false;
  WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
  SetRootComponent(WeaponMesh);
}

void AKODBaseWeapon::BeginPlay() {
  Super::BeginPlay();
  check(WeaponMesh);
  checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count`t be less or equal zero"));
  checkf(DefaultAmmo.Clips > 0, TEXT("Clips count`t be less or equal zero"));
  CurrentAmmo = DefaultAmmo;
}

void AKODBaseWeapon::MakeShot() {
  if(IsAmmoEmpty()) {
    UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
  }
}

bool AKODBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const {
  const auto KODCharecter = Cast<ACharacter>(GetOwner());
  if(!KODCharecter) return false;

  if(KODCharecter->IsPlayerControlled()) {
    const auto Controller = KODCharecter->GetController<APlayerController>();
    if(!Controller) return false;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
  } else {
    ViewLocation = GetMuzzleWorldLocation();
    ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
  }
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
  CollisionParams.bReturnPhysicalMaterial = true;
  GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void AKODBaseWeapon::DecreaseAmmo() {
  if(CurrentAmmo.Bullets == 0) {
    return;
  }
  CurrentAmmo.Bullets--;
  if(IsClipEmpty() && !IsAmmoEmpty()) {
    StopFire();
    OnClipEmpty.Broadcast(this);
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
}

bool AKODBaseWeapon::CanRealod() const {
  return  CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool AKODBaseWeapon::TryToAddAmmo(int32 ClipsAmount) {
  if(CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;
  if(IsAmmoEmpty()) {
    CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
    OnClipEmpty.Broadcast(this);
  }else if(CurrentAmmo.Clips < DefaultAmmo.Clips){
    const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
    if(DefaultAmmo.Clips - NextClipsAmount >= 0) {
      CurrentAmmo.Clips = NextClipsAmount;
    }else {
      CurrentAmmo.Clips = DefaultAmmo.Clips;
      CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    }
  }else {
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
  }
  return true;  
}

void AKODBaseWeapon::LogAmmo() {
  FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
  AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
}

bool AKODBaseWeapon::IsAmmoFull() const {
  return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

UNiagaraComponent* AKODBaseWeapon::SpawnMuzzleFX() {
  return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,
    WeaponMesh,
    MuzzleSocketName,
    FVector::ZeroVector,
    FRotator::ZeroRotator,
    EAttachLocation::SnapToTarget, true);
}

void AKODBaseWeapon::StartFire() {
}

void AKODBaseWeapon::StopFire() {
}
