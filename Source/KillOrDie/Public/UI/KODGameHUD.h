// Kill or Die

#pragma once

#include "CoreMinimal.h"
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
  TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
  TSubclassOf<UUserWidget> PauseWidgetClass;
  
  virtual void BeginPlay() override;
  
private:
  UPROPERTY()
  TMap<EKODMatchState, UUserWidget*> GameWidgets;
  
  UPROPERTY()
  UUserWidget* CurrentWidget = nullptr;
  
  void DrawCrossHair(); 
  void OnMatchStateChanged(EKODMatchState State);
};
