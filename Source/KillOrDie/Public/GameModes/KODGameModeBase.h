// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "KODCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "KODUtils.h"
#include "KODGameModeBase.generated.h"

class AAIController;
UCLASS()
class KILLORDIE_API AKODGameModeBase : public AGameModeBase {
  GENERATED_BODY()

public:
  AKODGameModeBase();
  virtual void StartPlay() override;
  virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
  
protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game")
  TSubclassOf<AAIController> AIControllerClass;
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game")
  TSubclassOf<APawn> AIPawnClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game")
  FGameData GameData;

private:
  void SpawnBots();
};
