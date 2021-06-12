// Kill or Die

#include "UI/KODPauseWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

void UKODPauseWidget::NativeOnInitialized() {
  Super::NativeOnInitialized();
  
  if(ClearPauseButton) {
    ClearPauseButton->OnClicked.AddDynamic(this, &UKODPauseWidget::OnClearPause);
  }
}

void UKODPauseWidget::OnClearPause() {
  if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

  GetWorld()->GetAuthGameMode()->ClearPause();
}
