// Kill or Die

#include "GameModes/KODGameModeBase.h"


#include "KODGameHUD.h"
#include "Characters/KODBaseCharacter.h"
#include "GameModes/KODPlayerController.h"
#include "AIController.h"

AKODGameModeBase::AKODGameModeBase() {
  DefaultPawnClass = AKODBaseCharacter::StaticClass();
  PlayerControllerClass = AKODPlayerController::StaticClass();
  HUDClass = AKODGameHUD::StaticClass();
}

void AKODGameModeBase::StartPlay() {
  Super::StartPlay();

  SpawnBots();
}

UClass* AKODGameModeBase::GetDefaultPawnClassForController_Implementation(
    AController* InController) {
  if(InController && InController->IsA<AAIController>()) {
    return AIPawnClass;
  }
  return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AKODGameModeBase::SpawnBots() {
  if(!GetWorld()) return;

  for (int32 i = 0; i < GameData.PlayerNum - 1; ++i) {
    FActorSpawnParameters SpawnInfo;
    SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    const auto KODAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
    RestartPlayer(KODAIController);
  }
}
