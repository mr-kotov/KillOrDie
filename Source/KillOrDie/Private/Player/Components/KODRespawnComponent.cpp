// Kill or Die

#include "Player/Components/KODRespawnComponent.h"

#include "KODGameModeBase.h"

UKODRespawnComponent::UKODRespawnComponent() {
  PrimaryComponentTick.bCanEverTick = false;
}

void UKODRespawnComponent::Respawn(int32 RespawnTime) {
  if(!GetWorld()) return;

  RespawnCountDown = RespawnTime;
  GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UKODRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

bool UKODRespawnComponent::IsRespawnInProgress() const {
  return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void UKODRespawnComponent::RespawnTimerUpdate() {
  if(--RespawnCountDown == 0) {
    if(!GetWorld()) return;
    GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

    const auto GameMode = Cast<AKODGameModeBase>(GetWorld()->GetAuthGameMode());
    if(!GameMode) return;

    GameMode->RespawnRequest(Cast<AController>(GetOwner()));
  }
}
