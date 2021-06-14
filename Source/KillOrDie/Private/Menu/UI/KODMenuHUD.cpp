// Kill or Die

#include "Menu/UI/KODMenuHUD.h"


#include "KODBaseWidget.h"
#include "Blueprint/UserWidget.h"

void AKODMenuHUD::BeginPlay() {
  Super::BeginPlay();

  if(MenuWidgetClass) {
    const auto MenuWidget = CreateWidget<UKODBaseWidget>(GetWorld(), MenuWidgetClass);
    if(MenuWidget) {
      MenuWidget->AddToViewport();
      MenuWidget->Show();
    }
  }
}
