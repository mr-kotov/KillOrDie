// Kill or Die

#include "Weapons/Components/KODWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

UKODWeaponFXComponent::UKODWeaponFXComponent() {
  PrimaryComponentTick.bCanEverTick = false;
}

void UKODWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) {
  auto Effect = DefaultEffect;
  if(Hit.PhysMaterial.IsValid()) {
    const auto PhysMat = Hit.PhysMaterial.Get();
    if(EffectsMap.Contains(PhysMat)) {
      Effect = EffectsMap[PhysMat];
    }
  }
  UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

