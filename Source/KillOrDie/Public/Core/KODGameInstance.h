// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KODGameInstance.generated.h"

UCLASS()
class KILLORDIE_API UKODGameInstance : public UGameInstance {
  GENERATED_BODY()

public:
  FName GetStartupLevelName() const {return StartLevelName;}
  FName GetMainMenuLevelName() const {return MainMenuLevelName;}
  
protected:
  UPROPERTY(EditDefaultsOnly, Category = "Game")
  FName StartLevelName = NAME_None;

  UPROPERTY(EditDefaultsOnly, Category = "Game")
  FName MainMenuLevelName = NAME_None;
};
