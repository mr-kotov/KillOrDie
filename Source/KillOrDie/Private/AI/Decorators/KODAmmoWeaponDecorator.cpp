// Kill or Die

#include "AI/Decorators/KODAmmoWeaponDecorator.h"
#include "KODUtils.h"
#include "Characters/Components/KODHealthComponent.h"
#include "AIController.h"
#include "KODWeaponComponent.h"

UKODAmmoWeaponDecorator::UKODAmmoWeaponDecorator() {
  NodeName = "Ammo Weapon";
}

bool UKODAmmoWeaponDecorator::CalculateRawConditionValue(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
  const auto Controller = OwnerComp.GetAIOwner();
  if(!Controller) return false;

  const auto HealthComponent = KODUtils::GetKODPlayerComponent<UKODHealthComponent>(Controller->GetPawn());
  if(!HealthComponent || HealthComponent->IsDead()) return false;

  const auto WeaponComponent = KODUtils::GetKODPlayerComponent<UKODWeaponComponent>(Controller->GetPawn());
  if(!WeaponComponent) return false;

  return WeaponComponent->NeedAmmo(WeaponType);
}
