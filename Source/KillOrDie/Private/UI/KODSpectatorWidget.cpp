// Kill or Die

#include "UI/KODSpectatorWidget.h"
#include "KODUtils.h"
#include "Components/KODRespawnComponent.h"

bool UKODSpectatorWidget::GetRespawnTimer(int32& CountDownTime) const {
  const auto RespawnComponent = KODUtils::GetKODPlayerComponent<UKODRespawnComponent>(GetOwningPlayer());
  if(!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

  CountDownTime = RespawnComponent->GetRespawnCountDown();
  return true;
}
