// Kill or Die


#include "Weapons/Launcher/KODLauncherWeapon.h"
#include "KDOProjectile.h"
#include "Kismet/GameplayStatics.h"

void AKODLauncherWeapon::StartFire() {
  MakeShot();
}

void AKODLauncherWeapon::MakeShot() {
  if(!GetWorld()) return;
  
  const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
  //откладываем выполнение beginPlay для настройки параметров спавна
  auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
  //set projectile params
  //завершаем спавна объекта, вызываем beginPlay
  UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}
