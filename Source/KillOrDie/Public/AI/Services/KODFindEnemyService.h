// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "KODFindEnemyService.generated.h"

UCLASS()
class KILLORDIE_API UKODFindEnemyService : public UBTService {
  GENERATED_BODY()
public:
  UKODFindEnemyService();

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  FBlackboardKeySelector EnemyActorKey;

  virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
