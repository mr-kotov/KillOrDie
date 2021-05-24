// Kill or Die

#include "AI/KDOAIController.h"

#include "AI/KODAICharacter.h"
#include "AI/Components/KODAIPerceptionComponent.h"

AKDOAIController::AKDOAIController() {
  KODAIPerceptionComponent = CreateDefaultSubobject<UKODAIPerceptionComponent>("KODPerceptionComponent");
  SetPerceptionComponent(*KODAIPerceptionComponent);  
}

void AKDOAIController::OnPossess(APawn* InPawn) {
  Super::OnPossess(InPawn);

  const auto KODCharacter = Cast<AKODAICharacter>(InPawn);
  if(KODCharacter) {
    RunBehaviorTree(KODCharacter->BehaviorTreeAsset);
  }
}

void AKDOAIController::Tick(float DeltaSeconds) {
  Super::Tick(DeltaSeconds);
  const auto AimActor = KODAIPerceptionComponent->GetClosestEnemy();
  SetFocus(AimActor);
}
