// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KODCoreTypes.h"
#include "KODGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class KILLORDIE_API UKODGameOverWidget : public UUserWidget {
  GENERATED_BODY()

protected:
  UPROPERTY(meta = (BindWidget))
  UVerticalBox* PlayerStatBox;

  UPROPERTY(meta = (BindWidget))
  UButton* ResetLevelButton;
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
  TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

  virtual void NativeOnInitialized() override;
private:
  void OnMatchStateChanged(EKODMatchState State);
  void UpdatePlayersStat();
  
  UFUNCTION()
  void OnResetLevel();
};
