// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KODGoToMenuWidget.generated.h"

class UButton;

UCLASS()
class KILLORDIE_API UKODGoToMenuWidget : public UUserWidget {
  GENERATED_BODY()
  
protected:
  UPROPERTY(meta = (BindWidget))
  UButton* GoToMenuButton;

  virtual void NativeOnInitialized() override;

private:
  UFUNCTION()
  void OnClickGoToMenu();
};
