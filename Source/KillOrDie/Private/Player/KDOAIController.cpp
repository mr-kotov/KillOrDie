// Kill or Die

#include "Player/KDOAIController.h"

#include "AI/KODAICharacter.h"
#include "AI/Components/KODAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/Components/KODRespawnComponent.h"

AKDOAIController::AKDOAIController() {
  KODAIPerceptionComponent = CreateDefaultSubobject<UKODAIPerceptionComponent>("KODPerceptionComponent");
  SetPerceptionComponent(*KODAIPerceptionComponent);
  bWantsPlayerState = true;

  RespawnComponent = CreateDefaultSubobject<UKODRespawnComponent>("RespawnComponent");
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
  const auto AimActor = GetFocusActor();
  SetFocus(AimActor);
}

AActor* AKDOAIController::GetFocusActor() const {
  if(!GetBlackboardComponent()) return nullptr;
  return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
