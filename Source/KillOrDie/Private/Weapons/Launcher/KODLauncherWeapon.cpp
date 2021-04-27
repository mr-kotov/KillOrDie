// Kill or Die


#include "Weapons/Launcher/KODLauncherWeapon.h"
#include "KDOProjectile.h"
#include "Kismet/GameplayStatics.h"

void AKODLauncherWeapon::StartFire() {
  MakeShot();
}

void AKODLauncherWeapon::MakeShot() {
  if(!GetWorld()) return;

  FVector TraceStart, TraceEnd;
  if(!GetTraceData(TraceStart, TraceEnd)) return;

  FHitResult HitResult;
  MakeHit(HitResult, TraceStart, TraceEnd);

  const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
  const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
  
  const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
  //откладываем выполнение beginPlay для настройки параметров спавна
  AKDOProjectile* Projectile = GetWorld()->SpawnActorDeferred<AKDOProjectile>(ProjectileClass, SpawnTransform);
  if(Projectile) {
    Projectile->SetShotDirection(Direction);
    Projectile->SetOwner(GetOwner());
    //завершаем спавна объекта, вызываем beginPlay
    Projectile->FinishSpawning(SpawnTransform);
  }
  //set projectile params
}
