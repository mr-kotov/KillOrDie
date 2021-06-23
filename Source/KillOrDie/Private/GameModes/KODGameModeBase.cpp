// Kill or Die

#include "GameModes/KODGameModeBase.h"


#include "KODGameHUD.h"
#include "Characters/KODBaseCharacter.h"
#include "Player/KODPlayerController.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "KODPlayerStart.h"
#include "KODPlayerState.h"
#include "KODUtils.h"
#include "Components/KODRespawnComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogKODGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

AKODGameModeBase::AKODGameModeBase() {
  DefaultPawnClass = AKODBaseCharacter::StaticClass();
  PlayerControllerClass = AKODPlayerController::StaticClass();
  HUDClass = AKODGameHUD::StaticClass();
  PlayerStateClass = AKODPlayerState::StaticClass();
}

void AKODGameModeBase::StartPlay() {
  Super::StartPlay();

  SpawnBots();
  CreateTeamsInfo();
  CurrentRound = 1;
  StartRound();

  SetMatchState(EKODMatchState::InProgress);
}

UClass* AKODGameModeBase::GetDefaultPawnClassForController_Implementation(
    AController* InController) {
  if(InController && InController->IsA<AAIController>()) {
    return AIPawnClass;
  }
  return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AKODGameModeBase::Killed(AController* KillerController,
                              AController* VictimController) {
  const auto KillerPlayerState = KillerController ? Cast<AKODPlayerState>(KillerController->PlayerState) : nullptr;
  const auto VictimPlayerState = VictimController ? Cast<AKODPlayerState>(VictimController->PlayerState) : nullptr;

  if(KillerPlayerState) {
    KillerPlayerState->AddKill();
  }

  if(VictimPlayerState) {
    VictimPlayerState->AddDeath();
  }
  StartRespawn(VictimController);
}

void AKODGameModeBase::RespawnRequest(AController* Controller) {
  ResetOnePlayer(Controller);
}

bool AKODGameModeBase::SetPause(APlayerController* PC,
    FCanUnpause CanUnpauseDelegate) {
  const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
  if(PauseSet) {
    SetMatchState(EKODMatchState::Pause);  
  }
  return PauseSet;
}

bool AKODGameModeBase::ClearPause() {
  const auto PauseCleared = Super::ClearPause();
  if(PauseCleared) {
    SetMatchState(EKODMatchState::InProgress);
  }
  return PauseCleared;
}

AActor* AKODGameModeBase::
ChoosePlayerStart_Implementation(AController* Player) {  
  const auto PlayerState = Cast<AKODPlayerState>(Player->PlayerState);
  if(PlayerState && PlayerState->GetPlayerStart())
    return PlayerState->GetPlayerStart();    

  for (auto PlayerStart: TActorRange<AKODPlayerStart>(GetWorld())) {
    if(PlayerStart && PlayerStart->GetIsFree()){
      PlayerStart->ToTake();

      if(PlayerState) {
        PlayerState->SetPlayerStart(PlayerStart);
        PlayerState->SetTeamID(PlayerStart->GetTeamID());
      }
      return PlayerStart;  
    }
  }
  return Super::ChoosePlayerStart_Implementation(Player);
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

void AKODGameModeBase::StartRound() {
  RoundCountDown = GameData.RoundTime;
  GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AKODGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AKODGameModeBase::GameTimerUpdate() {
  //UE_LOG(LogKODGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);
  if(--RoundCountDown == 0) {
    GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
    if(CurrentRound + 1 <= GameData.RoundsNum) {
      ++CurrentRound;
      ResetPlayers();
      StartRound();
    }else {
      GameOver();
    }
  }
}

void AKODGameModeBase::ResetPlayers() {
  if(!GetWorld()) return;

  for (auto It = GetWorld()->GetControllerIterator(); It; ++It) {
    ResetOnePlayer(It->Get());
  }
}

void AKODGameModeBase::ResetOnePlayer(AController* Controller) {
  if(Controller && Controller->GetPawn()) {
    Controller->GetPawn()->Reset();
  }
  RestartPlayer(Controller);
  SetPlayerColor(Controller);
}

void AKODGameModeBase::CreateTeamsInfo() {
  if(!GetWorld()) return;

  for (auto It = GetWorld()->GetControllerIterator(); It; ++It) {
    const auto Controller = It->Get();
    if(!Controller) continue;

    const auto PlayerState = Cast<AKODPlayerState>(Controller->PlayerState);
    if(!PlayerState) continue;

    PlayerState->SetTeamColor(DetermineColorByTeamID(PlayerState->GetTeamID()));
    PlayerState->SetPlayerName(Controller->IsPlayerController()? "Player" : "Bot");
    SetPlayerColor(Controller);
  }
}

FLinearColor AKODGameModeBase::DetermineColorByTeamID(int32 TeamID) const {
  if(TeamID - 1 < GameData.TeamColors.Num()) {
    return  GameData.TeamColors[TeamID - 1];
  }
  return GameData.DefaultTeamColor;
}

void AKODGameModeBase::SetPlayerColor(AController* Controller) {
  if(!Controller) return;

  const auto Character = Cast<AKODBaseCharacter>(Controller->GetPawn());
  if(!Character) return;

  const auto PlayerState = Cast<AKODPlayerState>(Controller->PlayerState);
  if(!PlayerState) return;

  Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AKODGameModeBase::LogPlayerInfo() {
  if(!GetWorld()) return;

  for (auto It = GetWorld()->GetControllerIterator(); It; ++It) {
    const auto Controller = It->Get();
    if(!Controller) continue;

    const auto PlayerState = Cast<AKODPlayerState>(Controller->PlayerState);
    if(!PlayerState) continue;

    PlayerState->LogInfo();
  }
}

void AKODGameModeBase::StartRespawn(AController* Controller) {
  const auto RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
  if(!RespawnAvailable) return;
  
  const auto RespawnComponent = KODUtils::GetKODPlayerComponent<UKODRespawnComponent>(Controller);
  if(!RespawnComponent) return;

  RespawnComponent->Respawn(GameData.RespawnTime);
}

void AKODGameModeBase::GameOver() {
  UE_LOG(LogKODGameModeBase, Display, TEXT("=============== GAME OVER =============="));
  LogPlayerInfo();

  for (auto Pawn: TActorRange<APawn>(GetWorld())) {
    if(Pawn) {
      Pawn->TurnOff();
      Pawn->DisableInput(nullptr);
    }
  }
  SetMatchState(EKODMatchState::GameOver);
}

void AKODGameModeBase::SetMatchState(EKODMatchState State) {
  if(MatchState == State) return;

  MatchState = State;
  OnMatchStateChanged.Broadcast(MatchState);
}
