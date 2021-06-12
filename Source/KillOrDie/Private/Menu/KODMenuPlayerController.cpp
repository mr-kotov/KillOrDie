// Kill or Die

#include "Menu/KODMenuPlayerController.h"

void AKODMenuPlayerController::BeginPlay() {
  Super::BeginPlay();

  SetInputMode(FInputModeUIOnly());
  bShowMouseCursor = true;
}
