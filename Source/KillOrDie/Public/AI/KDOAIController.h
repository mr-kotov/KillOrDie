// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KDOAIController.generated.h"

UCLASS()
class KILLORDIE_API AKDOAIController : public AAIController {
  GENERATED_BODY()
protected:
  virtual void OnPossess(APawn* InPawn) override;
};
