// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KODCoreTypes.h" 
#include "KODPlayerHUDWidget.generated.h"

UCLASS()
class KILLORDIE_API UKODPlayerHUDWidget : public UUserWidget {
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, Category = "UI")
  float GetHealthPercent() const;

  UFUNCTION(BlueprintCallable, Category = "UI")
  bool GetWeaponUIData(FWeaponUIData& UIData) const;
};
