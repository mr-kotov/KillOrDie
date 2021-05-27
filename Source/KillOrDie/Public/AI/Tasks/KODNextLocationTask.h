// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "KODNextLocationTask.generated.h"

UCLASS()
class KILLORDIE_API UKODNextLocationTask : public UBTTaskNode {
  GENERATED_BODY()

public:
  UKODNextLocationTask();

  virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  float Radius = 1000.0f;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  FBlackboardKeySelector AimLocationKey;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  bool SelfCenter = true;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SelfCenter"))
  FBlackboardKeySelector CenterActorKey;
};
