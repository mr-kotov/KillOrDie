// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "KODAmmoWeaponDecorator.generated.h"

class AKODBaseWeapon;

UCLASS()
class KILLORDIE_API UKODAmmoWeaponDecorator : public UBTDecorator {
  GENERATED_BODY()
public:
  UKODAmmoWeaponDecorator();
protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  TSubclassOf<AKODBaseWeapon> WeaponType;
  
  virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
