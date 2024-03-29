// Kill or Die


#include "Weapons/Launcher/KODLauncherWeapon.h"
#include "KDOProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void AKODLauncherWeapon::StartFire() {
  MakeShot();
}

void AKODLauncherWeapon::MakeShot() {
  Super::MakeShot();
  
  if(!GetWorld() || IsAmmoEmpty()) return;

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
  DecreaseAmmo();
  SpawnMuzzleFX();
  UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
  //UE_LOG(LogTemp, Error, TEXT("location: %s"), *GetOwner()->GetActorLocation().ToString())
  //set projectile params
}
