// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTDecorator.h"
#include "KDOHealthPercentDecorator.generated.h"

UCLASS()
class KILLORDIE_API UKDOHealthPercentDecorator : public UBTDecorator {
  GENERATED_BODY()
public:
  UKDOHealthPercentDecorator();
  
protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  float HealthPercent = 0.6f;
  
  virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
