// Kill or Die

#include "UI/KODPauseWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

bool UKODPauseWidget::Initialize() {
  const auto InitState = Super::Initialize();

  if(ClearPauseButton) {
    ClearPauseButton->OnClicked.AddDynamic(this, &UKODPauseWidget::OnClearPause);
  }
  return InitState;
}

void UKODPauseWidget::OnClearPause() {
  if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

  GetWorld()->GetAuthGameMode()->ClearPause();
}
