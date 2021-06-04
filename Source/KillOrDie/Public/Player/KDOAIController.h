// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KDOAIController.generated.h"

class UKODAIPerceptionComponent;
UCLASS()
class KILLORDIE_API AKDOAIController : public AAIController {
  GENERATED_BODY()
public:
  AKDOAIController();
protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UKODAIPerceptionComponent* KODAIPerceptionComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
  FName FocusOnKeyName = "EnemyActor";
  
  virtual void OnPossess(APawn* InPawn) override;
  virtual void Tick(float DeltaSeconds) override;

private:
  AActor* GetFocusActor() const;
};
