// Kill or Die

#include "AI/KDOAIController.h"

#include "KODAICharacter.h"

void AKDOAIController::OnPossess(APawn* InPawn) {
  Super::OnPossess(InPawn);

  const auto KODCharacter = Cast<AKODAICharacter>(InPawn);
  if(KODCharacter) {
    RunBehaviorTree(KODCharacter->BehaviorTreeAsset);
  }
}
