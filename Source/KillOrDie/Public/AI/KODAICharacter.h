// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Characters/KODBaseCharacter.h"
#include "KODAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class KILLORDIE_API AKODAICharacter : public AKODBaseCharacter {
  GENERATED_BODY()

public:
  AKODAICharacter(const FObjectInitializer& ObjInit);

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
  UBehaviorTree* BehaviorTreeAsset;

  virtual void Tick(float DeltaSeconds) override;
protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UWidgetComponent* HealthWidgetComponent;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
  float HealthVisibilityDistance = 1000.0f;
  
  virtual void BeginPlay() override;  
  virtual void OnDeath() override;
  virtual void OnHealthChanged(float Health, float HealthDelta) override;
private:
  void UpdateHealthWidgetVisibility();
};
