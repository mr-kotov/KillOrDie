// Kill or Die

#include "AI/Tasks/KODNextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UKODNextLocationTask::UKODNextLocationTask() {
  NodeName = "Next Location";
}

EBTNodeResult::Type UKODNextLocationTask::ExecuteTask(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
  UE_LOG(LogTemp, Warning, TEXT("ExecuteTask"));
  const auto Controller = OwnerComp.GetAIOwner();
  const auto Blackboard = OwnerComp.GetBlackboardComponent();

  if(!Controller || !Blackboard) return EBTNodeResult::Failed;

  const auto Pawn = Controller->GetPawn();
  if(!Pawn) return EBTNodeResult::Failed;

  const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
  if(!NavSys) return EBTNodeResult::Failed;

  FNavLocation NavLocation;
  const auto Found = NavSys->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavLocation);
  if(!Found) return EBTNodeResult::Failed;

  Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
  UE_LOG(LogTemp, Warning, TEXT("ExecuteTask"));
  return EBTNodeResult::Succeeded;
}
