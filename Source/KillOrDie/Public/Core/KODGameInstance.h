// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KODCoreTypes.h"
#include "KODGameInstance.generated.h"

UCLASS()
class KILLORDIE_API UKODGameInstance : public UGameInstance {
  GENERATED_BODY()

public:
  FLevelData GetStartupLevel() const {return StartupLevel;}
  void SetStartupLevel(const FLevelData& Data) {StartupLevel = Data;}
  TArray<FLevelData> GetLevelsData() const {return  LevelsData;}
  FName GetMainMenuLevelName() const {return MainMenuLevelName;}
  
protected:
  UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Level names must be unique!"))
  TArray<FLevelData> LevelsData;
 
  UPROPERTY(EditDefaultsOnly, Category = "Game")
  FName MainMenuLevelName = NAME_None;

private:
  FLevelData StartupLevel;
};
