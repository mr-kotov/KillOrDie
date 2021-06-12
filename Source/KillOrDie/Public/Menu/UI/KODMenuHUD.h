// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KODMenuHUD.generated.h"

UCLASS()
class KILLORDIE_API AKODMenuHUD : public AHUD {
  GENERATED_BODY()
protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
  TSubclassOf<UUserWidget> MenuWidgetClass;
  
  virtual void BeginPlay() override;
};
