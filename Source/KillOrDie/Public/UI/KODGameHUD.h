// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "KODBaseWidget.h"
#include "GameFramework/HUD.h"
#include "KODCoreTypes.h"
#include "KODGameHUD.generated.h"

UCLASS()
class KILLORDIE_API AKODGameHUD : public AHUD {
  GENERATED_BODY()

public:
  virtual void DrawHUD() override;

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
  TSubclassOf<UKODBaseWidget> PlayerHUDWidgetClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
  TSubclassOf<UKODBaseWidget> PauseWidgetClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
  TSubclassOf<UKODBaseWidget> GameOverWidgetClass;
  
  virtual void BeginPlay() override;
  
private:
  UPROPERTY()
  TMap<EKODMatchState, UKODBaseWidget*> GameWidgets;
  
  UPROPERTY()
  UKODBaseWidget* CurrentWidget = nullptr;
  
  void DrawCrossHair(); 
  void OnMatchStateChanged(EKODMatchState State);
};
