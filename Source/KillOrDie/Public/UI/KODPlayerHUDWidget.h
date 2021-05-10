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
  bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
  
  UFUNCTION(BlueprintCallable, Category = "UI")
  bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

  UFUNCTION(BlueprintCallable, Category = "UI")
  bool IsPlayerAlive() const;

  UFUNCTION(BlueprintCallable, Category = "UI")
  bool IsPlayerSpectating() const;
};
