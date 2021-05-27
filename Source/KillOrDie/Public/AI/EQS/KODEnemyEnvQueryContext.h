// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "KODEnemyEnvQueryContext.generated.h"

UCLASS()
class KILLORDIE_API UKODEnemyEnvQueryContext : public UEnvQueryContext {
  GENERATED_BODY()
public:
  virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  FName EnemyActorKeyName = "EnemyActor";
};
