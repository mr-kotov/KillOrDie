// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KODSpectatorWidget.generated.h"

UCLASS()
class KILLORDIE_API UKODSpectatorWidget : public UUserWidget {
  GENERATED_BODY()
public:
  UFUNCTION(BlueprintCallable, Category = "UI")
  bool GetRespawnTimer(int32& CountDownTime) const;
};
