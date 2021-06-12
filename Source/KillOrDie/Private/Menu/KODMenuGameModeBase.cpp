// Kill or Die


#include "Menu/KODMenuGameModeBase.h"


#include "Menu/KODMenuPlayerController.h"
#include "Menu/UI/KODMenuHUD.h"

AKODMenuGameModeBase::AKODMenuGameModeBase() {
  PlayerControllerClass = AKODMenuPlayerController::StaticClass();
  HUDClass = AKODMenuHUD::StaticClass();
}
