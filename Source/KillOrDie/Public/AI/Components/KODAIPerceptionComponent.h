// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "KODAIPerceptionComponent.generated.h"

UCLASS()
class KILLORDIE_API UKODAIPerceptionComponent : public UAIPerceptionComponent {
  GENERATED_BODY()
public:
  AActor* GetClosestEnemy() const;
};
