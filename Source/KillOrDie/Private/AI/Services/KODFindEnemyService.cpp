// Kill or Die

#include "AI/Services/KODFindEnemyService.h"

#include "KODAIPerceptionComponent.h"
#include "KODUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UKODFindEnemyService::UKODFindEnemyService() {
  NodeName = "Find Enemy";
}

void UKODFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp,
                                    uint8* NodeMemory, float DeltaSeconds) {
  const auto Blackboard = OwnerComp.GetBlackboardComponent();
  if(Blackboard) {
    const auto Controller = OwnerComp.GetAIOwner();
    const auto PerceptionComponent = KODUtils::GetKODPlayerComponent<UKODAIPerceptionComponent>(Controller);
    if(PerceptionComponent) {
      Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
    }
  }
  Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
