// Kill or Die

#include "Menu/UI/KODGoToMenuWidget.h"


#include "KODGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogUKODGoToMenuWidget, All, All);

void UKODGoToMenuWidget::NativeOnInitialized() {
  Super::NativeOnInitialized();

  if(GoToMenuButton) {
    GoToMenuButton->OnClicked.AddDynamic(this, &UKODGoToMenuWidget::OnClickGoToMenu);
  }
}

void UKODGoToMenuWidget::OnClickGoToMenu() {
  if(!GetWorld()) return;

  const auto KODGameInstance = GetWorld()->GetGameInstance<UKODGameInstance>();
  if(KODGameInstance->GetMainMenuLevelName().IsNone()) {
    UE_LOG(LogUKODGoToMenuWidget, Error, TEXT("Menu level name is NONE"));
    return;
  }
  UGameplayStatics::OpenLevel(this, KODGameInstance->GetMainMenuLevelName());
}
