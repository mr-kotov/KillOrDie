// Kill or Die

#include "GameModes/KODGameModeBase.h"

#include "Characters/KODBaseCharacter.h"
#include "GameModes/KODPlayerController.h"

AKODGameModeBase::AKODGameModeBase() {
  DefaultPawnClass = AKODBaseCharacter::StaticClass();
  PlayerControllerClass = AKODPlayerController::StaticClass();
}
