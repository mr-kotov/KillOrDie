// Kill or Die

#include "AI/Services/KODChangeWeaponService.h"
#include "KODUtils.h"
#include "AIController.h"
#include "Weapons/Components/KODAIWeaponComponent.h"

UKODChangeWeaponService::UKODChangeWeaponService() {
  NodeName = "Change Weapon";
}

void UKODChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp,
    uint8* NodeMemory, float DeltaSeconds) {
  const auto Controller = OwnerComp.GetAIOwner();
  if(Controller) {
    const auto WeaponComponent = KODUtils::GetKODPlayerComponent<UKODAIWeaponComponent>(Controller->GetPawn());
    if(WeaponComponent && Probability > 0 && FMath::FRand() <= Probability) {
      WeaponComponent->NextWeapon();
    }
  }

  Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
