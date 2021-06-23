// Kill or Die

#include "Weapons/Rifle/KODRifleWeapon.h"
#include "Weapons/Components/KODWeaponFXComponent.h"
#include "DrawDebugHelpers.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRifleWeapon, All, All);

AKODRifleWeapon::AKODRifleWeapon() {
  WeaponFXComponent = CreateDefaultSubobject<UKODWeaponFXComponent>("WeaponFXComponent");
}
void AKODRifleWeapon::BeginPlay() {
  Super::BeginPlay();

  check(WeaponFXComponent);
}

void AKODRifleWeapon::StartFire() {
  InitFX();
  GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AKODRifleWeapon::MakeShot, TimerBetweenShots, true, 0.2f);
  MakeShot();
}

void AKODRifleWeapon::StopFire() {
  GetWorldTimerManager().ClearTimer(ShotTimerHandle);
  SetFXActive(false);
}

void AKODRifleWeapon::Zoom(bool Enabled) {
  const auto Controller = Cast<APlayerController>(GetController());
  if(!Controller || !Controller->PlayerCameraManager) return;

  if(Enabled) {
    DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
  }
  IsZoom = Enabled;
  //const TInterval<float> FOV(50.0f,90.0f);
  Controller->PlayerCameraManager->SetFOV(Enabled ? FOVZoomAngle : DefaultCameraFOV);
}

void AKODRifleWeapon::MakeShot() {
  Super::MakeShot();
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

  FVector TraceFXEnd = TraceEnd;
  if(HitResult.bBlockingHit) {
    TraceFXEnd = HitResult.ImpactPoint;
    MakeDamage(HitResult);
    WeaponFXComponent->PlayImpactFX(HitResult);
  }
  SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
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
  const auto HalfRad = FMath::DegreesToRadians(IsZoom ? BulletSpreadZoom : BulletSpread);
  const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);//SocketTransform.GetRotation().GetForwardVector();
  /**Получаем последнюю точку для формирования траектории стрельбы*/
  TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
  return true;
}

void AKODRifleWeapon::MakeDamage(const FHitResult& HitResult) {
  const auto DamgeActor = HitResult.GetActor();
  if(!DamgeActor) return;

  FPointDamageEvent PointDamageEvent;
  PointDamageEvent.HitInfo = HitResult;
  
  DamgeActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}

void AKODRifleWeapon::InitFX() {
  if(!MuzzleFXComponent) {
    MuzzleFXComponent = SpawnMuzzleFX();
  }
  if(!FireAudioComponent) {
    FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
  }
  SetFXActive(true);
}

void AKODRifleWeapon::SetFXActive(bool IsActive) {
  if(MuzzleFXComponent) {
    MuzzleFXComponent->SetPaused(!IsActive);
    MuzzleFXComponent->SetVisibility(IsActive, true);
  }
  if(FireAudioComponent) {
    IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
  }
}

void AKODRifleWeapon::SpawnTraceFX(const FVector& TraceStart,
    const FVector& TraceEnd) {
  const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
  if(TraceFXComponent) {
    TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
  }
}

AController* AKODRifleWeapon::GetController() const {
  const auto Pawn = Cast<APawn>(GetOwner());
  return Pawn ? Pawn->GetController() : nullptr;
}
