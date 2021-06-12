// Kill or Die

#include "Menu/UI/KODMenuWidget.h"


#include "KODGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogUKODMenuWidget, All, All);

void UKODMenuWidget::NativeOnInitialized() {
  Super::NativeOnInitialized();

  if(StartGameButton) {
    StartGameButton->OnClicked.AddDynamic(this, &UKODMenuWidget::OnStartGame);
  }

  if(QuitGameButton) {
    QuitGameButton->OnClicked.AddDynamic(this, &UKODMenuWidget::OnQuitGame);
  }
}

void UKODMenuWidget::OnStartGame() {
  if(!GetWorld()) return;

  const auto KODGameInstance = GetWorld()->GetGameInstance<UKODGameInstance>();
  if(KODGameInstance->GetStartupLevelName().IsNone()) {
    UE_LOG(LogUKODMenuWidget, Error, TEXT("Start level name is NONE"));
    return;
  }
  UGameplayStatics::OpenLevel(this, KODGameInstance->GetStartupLevelName());
}

void UKODMenuWidget::OnQuitGame() {
  UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
