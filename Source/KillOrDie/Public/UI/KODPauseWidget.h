// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "KODBaseWidget.h"
#include "KODPauseWidget.generated.h"

class UButton;

UCLASS()
class KILLORDIE_API UKODPauseWidget : public UKODBaseWidget {
  GENERATED_BODY()  
protected:
  UPROPERTY(meta = (BindWidget))
  UButton* ClearPauseButton;

  virtual void NativeOnInitialized() override;
private:
  UFUNCTION()
  void OnClearPause();
};
