// Kill or Die

#include "Weapons/Components/KODWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

UKODWeaponFXComponent::UKODWeaponFXComponent() {
  PrimaryComponentTick.bCanEverTick = false;
}

void UKODWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) {
  auto ImpactData = DefaultEffectData;
  if(Hit.PhysMaterial.IsValid()) {
    const auto PhysMat = Hit.PhysMaterial.Get();
    if(ImpactDataMap.Contains(PhysMat)) {
      ImpactData = ImpactDataMap[PhysMat];
    }
  }
  //niagara
  UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
    ImpactData.NiagaraEffect,
    Hit.ImpactPoint,
    Hit.ImpactNormal.Rotation());

  //decal
  auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
    ImpactData.DecalData.Material,
    ImpactData.DecalData.Size,
    Hit.ImpactPoint,
    Hit.ImpactNormal.Rotation());
  if(DecalComponent) {
    DecalComponent->SetFadeOut(ImpactData.DecalData.LiftTime, ImpactData.DecalData.FadeOutTime);
  }
}

