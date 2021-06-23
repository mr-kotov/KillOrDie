// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "KODCoreTypes.h"
#include "KODPlayerStart.h"
#include "GameFramework/GameModeBase.h"
#include "KODUtils.h"
#include "KODGameModeBase.generated.h"

class AAIController;
UCLASS()
class KILLORDIE_API AKODGameModeBase : public AGameModeBase {
  GENERATED_BODY()

public:
  AKODGameModeBase();

  FOnMatchStateChangedSignature OnMatchStateChanged;
  
  virtual void StartPlay() override;
  virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
  //virtual void FindPlayerStart_Implementation();

  void Killed(AController* KillerController, AController* VictimController);
  FGameData GetGameData() const {return  GameData;}
  int32 GetCurrentRoundNum() const {return  CurrentRound;}
  int32 GetRoundSecondsRemaining() const {return RoundCountDown;}
  void RespawnRequest(AController* Controller);
protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game")
  TSubclassOf<AAIController> AIControllerClass;
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game")
  TSubclassOf<APawn> AIPawnClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game")
  FGameData GameData;

  virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
  virtual bool ClearPause() override;
  virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
  
private:
  EKODMatchState MatchState = EKODMatchState::WaitingToStart; 
  int32 CurrentRound = 1;
  int32 RoundCountDown = 0;
  FTimerHandle GameRoundTimerHandle;
  
  void SpawnBots();
  void StartRound();
  void GameTimerUpdate();

  void ResetPlayers();
  void ResetOnePlayer(AController* Controller);

  void CreateTeamsInfo();
  FLinearColor DetermineColorByTeamID(int32 TeamID) const;
  void SetPlayerColor(AController* Controller);

  void LogPlayerInfo();
  void StartRespawn(AController* Controller);
  void GameOver();
  void SetMatchState(EKODMatchState State);
};
