// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KODWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KILLORDIE_API UKODWeaponFXComponent : public UActorComponent {
  GENERATED_BODY()

public:
  UKODWeaponFXComponent();

  void PlayImpactFX(const FHitResult& Hit);

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  UNiagaraSystem* DefaultEffect;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;
};
