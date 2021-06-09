// Kill or Die


#include "Player/KODPlayerController.h"
#include "KODGameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "Player/Components/KODRespawnComponent.h"

AKODPlayerController::AKODPlayerController() {
  RespawnComponent = CreateDefaultSubobject<UKODRespawnComponent>("RespawnComponent");
}

void AKODPlayerController::BeginPlay() {
  Super::BeginPlay();

  if(GetWorld()) {
    const auto GameMode = Cast<AKODGameModeBase>(GetWorld()->GetAuthGameMode());
    if(GameMode) {
      GameMode->OnMatchStateChanged.AddUObject(this, &AKODPlayerController::OnMatchStateChanged);
    }
  }
}

void AKODPlayerController::SetupInputComponent() {
  Super::SetupInputComponent();
  if(!InputComponent) return;

  InputComponent->BindAction("PauseGame", IE_Pressed, this, &AKODPlayerController::OnPauseGame);
}

void AKODPlayerController::OnPauseGame() {
  if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

  GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AKODPlayerController::OnMatchStateChanged(EKODMatchState State) {
  if(State == EKODMatchState::InProgress) {
    SetInputMode(FInputModeGameOnly());
    bShowMouseCursor = false;
  }else {
    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
  }
}
