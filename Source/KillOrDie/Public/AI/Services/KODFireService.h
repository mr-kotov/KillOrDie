// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "KODFireService.generated.h"

UCLASS()
class KILLORDIE_API UKODFireService : public UBTService {
  GENERATED_BODY()
public:
  UKODFireService();

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  FBlackboardKeySelector EnemyActorKey;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  bool LetShoot = true;

  virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
