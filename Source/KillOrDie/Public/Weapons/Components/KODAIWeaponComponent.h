// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Components/KODWeaponComponent.h"
#include "KODAIWeaponComponent.generated.h"

UCLASS()
class KILLORDIE_API UKODAIWeaponComponent : public UKODWeaponComponent {
  GENERATED_BODY()
public:
  virtual void StartFire() override;
  virtual void NextWeapon() override;
};
