// Kill or Die


#include "Player/KODPlayerController.h"
#include "Player/Components/KODRespawnComponent.h"

AKODPlayerController::AKODPlayerController() {
  RespawnComponent = CreateDefaultSubobject<UKODRespawnComponent>("RespawnComponent");
}
