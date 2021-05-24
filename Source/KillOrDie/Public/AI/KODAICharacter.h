// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Characters/KODBaseCharacter.h"
#include "KODAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class KILLORDIE_API AKODAICharacter : public AKODBaseCharacter {
  GENERATED_BODY()

public:
  AKODAICharacter(const FObjectInitializer& ObjInit);

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
  UBehaviorTree* BehaviorTreeAsset;
};
