// Kill or Die

#include "UI/KODGameDataWidget.h"
#include "KODGameModeBase.h"
#include "KODPlayerState.h"

int32 UKODGameDataWidget::GetCurrentRoundNum() const {
  const auto GameMode = GetKODGameMode();
  return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 UKODGameDataWidget::GetTotalRoundsNum() const {
  const auto GameMode = GetKODGameMode();
  return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UKODGameDataWidget::GetRoundSecondsRemaining() const{
  const auto GameMode = GetKODGameMode();
  return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

AKODPlayerState* UKODGameDataWidget::GetKODPlayerState() const {
  return GetOwningPlayer() ? Cast<AKODPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}

AKODGameModeBase* UKODGameDataWidget::GetKODGameMode() const {
  return GetWorld() ? Cast<AKODGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}
