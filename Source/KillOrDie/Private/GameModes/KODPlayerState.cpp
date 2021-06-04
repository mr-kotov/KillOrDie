// Kill or Die

#include "GameModes/KODPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogKODPlayerState, All, All);

void AKODPlayerState::LogInfo() {
  UE_LOG(LogKODPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
