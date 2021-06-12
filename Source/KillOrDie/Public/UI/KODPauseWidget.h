// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KODPauseWidget.generated.h"

class UButton;

UCLASS()
class KILLORDIE_API UKODPauseWidget : public UUserWidget {
  GENERATED_BODY()  
protected:
  UPROPERTY(meta = (BindWidget))
  UButton* ClearPauseButton;

  virtual void NativeOnInitialized() override;
private:
  UFUNCTION()
  void OnClearPause();
};
