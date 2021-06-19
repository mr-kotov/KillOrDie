// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KODBaseWidget.generated.h"

class USoundCue;

UCLASS()
class KILLORDIE_API UKODBaseWidget : public UUserWidget {
  GENERATED_BODY()

public:
  void Show();
  
protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
  USoundCue* OpenSound;
  
  UPROPERTY(meta = (BindWidgetAnim), Transient)
  UWidgetAnimation* ShowAnimation;
};
