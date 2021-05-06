// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KODGameHUD.generated.h"

UCLASS()
class KILLORDIE_API AKODGameHUD : public AHUD {
  GENERATED_BODY()

public:
  virtual void DrawHUD() override;

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
  TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

  virtual void BeginPlay() override;
  
private:
  void DrawCrossHair(); 
  
};
