// Kill or Die

#include "Menu/UI/KODMenuHUD.h"

#include "Blueprint/UserWidget.h"

void AKODMenuHUD::BeginPlay() {
  Super::BeginPlay();

  if(MenuWidgetClass) {
    const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
    if(MenuWidget) {
      MenuWidget->AddToViewport();
    }
  }
}
