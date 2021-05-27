// Kill or Die

#include "AI/Decorators/KDOHealthPercentDecorator.h"
#include "KODUtils.h"
#include "AIController.h"
#include "Characters/Components/KODHealthComponent.h"

UKDOHealthPercentDecorator::UKDOHealthPercentDecorator() {
  NodeName = "Health Percent";
}

bool UKDOHealthPercentDecorator::CalculateRawConditionValue(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
  const auto Controller = OwnerComp.GetAIOwner();
  if(!Controller) return false;

  const auto HealthComponent = KODUtils::GetKODPlayerComponent<UKODHealthComponent>(Controller->GetPawn());
  if(!HealthComponent || HealthComponent->IsDead()) return false;

  return HealthComponent->GetHealthPercent() <= HealthPercent;
}
