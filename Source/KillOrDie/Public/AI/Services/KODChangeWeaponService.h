// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "KODChangeWeaponService.generated.h"

UCLASS()
class KILLORDIE_API UKODChangeWeaponService : public UBTService {
  GENERATED_BODY()
public:
  UKODChangeWeaponService();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
  float Probability = 0.5f;

  virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
