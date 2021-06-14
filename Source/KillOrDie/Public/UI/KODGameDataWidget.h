// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "KODGameDataWidget.generated.h"
class AKODGameModeBase;
class AKODPlayerState;

UCLASS()
class KILLORDIE_API UKODGameDataWidget : public UUserWidget {
  GENERATED_BODY()
public:  
  UFUNCTION(BlueprintCallable, Category = "UI")
  int32 GetCurrentRoundNum() const;
  
  UFUNCTION(BlueprintCallable, Category = "UI")
  int32 GetTotalRoundsNum() const;
  
  UFUNCTION(BlueprintCallable, Category = "UI")
  int32 GetRoundSecondsRemaining() const;
private:
  AKODGameModeBase* GetKODGameMode() const;
  AKODPlayerState* GetKODPlayerState() const;
};
