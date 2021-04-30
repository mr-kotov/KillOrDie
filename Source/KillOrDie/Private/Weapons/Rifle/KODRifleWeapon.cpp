// Kill or Die

#include "Weapons/Rifle/KODRifleWeapon.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogRifleWeapon, All, All);
void AKODRifleWeapon::StartFire() {
  MakeShot();
  GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AKODRifleWeapon::MakeShot, TimerBetweenShots, true, 0.2f);
}

void AKODRifleWeapon::StopFire() {
  GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void AKODRifleWeapon::MakeShot() {
  if(!GetWorld() || IsAmmoEmpty()) {
    StopFire();
    return;
  }

  FVector TraceStart, TraceEnd;
  if(!GetTraceData(TraceStart, TraceEnd)) {
    StopFire();
    return;
  }

  FHitResult HitResult;
  MakeHit(HitResult, TraceStart, TraceEnd);
  
  if(HitResult.bBlockingHit) {
    MakeDamage(HitResult);
    DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 1.0f, 0, 3.0f);
    DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 1.0f);
  } else {
    DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Blue, false, 3.0f, 0, 5.0f);
  }
  DecreaseAmmo();
}

bool AKODRifleWeapon::
GetTraceData(FVector& TraceStart, FVector& TraceEnd) const {
  FVector ViewLocation;
  FRotator ViewRotation;
  if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
  
  /**Получаем положенее в мире, начало траектории*/
  TraceStart = ViewLocation;//SocketTransform.GetLocation();
  /**Получаем направление стрельбы*/
  const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
  const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);//SocketTransform.GetRotation().GetForwardVector();
  /**Получаем последнюю точку для формирования траектории стрельбы*/
  TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
  return true;
}

void AKODRifleWeapon::MakeDamage(const FHitResult& HitResult) {
  const auto DamgeActor = HitResult.GetActor();
  if(!DamgeActor) return;
  DamgeActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}
