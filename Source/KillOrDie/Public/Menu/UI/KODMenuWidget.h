// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "KODBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "KODCoreTypes.h"
#include "KODMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UKODGameInstance;
class UKODLevelItemWidget;

UCLASS()
class KILLORDIE_API UKODMenuWidget : public UKODBaseWidget {
  GENERATED_BODY()

protected:
  UPROPERTY(meta = (BindWidget))
  UButton* StartGameButton;

  UPROPERTY(meta = (BindWidget))
  UButton* QuitGameButton;

  UPROPERTY(meta = (BindWidget))
  UHorizontalBox* LevelItemBox;
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
  TSubclassOf<UUserWidget> LevelItemWidgetClass;

  UPROPERTY(meta = (BindWidgetAnim), Transient)
  UWidgetAnimation* HideAnimation;
  
  virtual void NativeOnInitialized() override;
  virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
UPROPERTY()
  TArray<UKODLevelItemWidget*> LevelItemWidgets;
  
  UFUNCTION()
  void OnStartGame();

  UFUNCTION()
  void OnQuitGame();

  void InitLevelItems();
  void OnLevelSelected(const FLevelData& Data);
  UKODGameInstance* GetKODGameInstance() const;
};
