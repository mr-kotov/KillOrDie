// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "KODPlayerStart.h"
#include "GameFramework/PlayerState.h"
#include "KODPlayerState.generated.h"

UCLASS()
class KILLORDIE_API AKODPlayerState : public APlayerState {
  GENERATED_BODY()
public:
  void SetTeamID(int32 ID){TeamID = ID;}
  int32 GetTeamID() const {return TeamID;}

  void SetTeamColor(const FLinearColor& Color) {TeamColor = Color;}
  FLinearColor GetTeamColor() const {return TeamColor;}

  void AddKill(){++KillsNum;}
  int32 GetKillsNum() const {return KillsNum;}

  void AddDeath(){++DeathsNum;}
  int32 GetDeathsNum() const {return  DeathsNum;}

  AKODPlayerStart* GetPlayerStart(){return PlayerStart;}
  void SetPlayerStart(AKODPlayerStart* PlayerStartVal){PlayerStart = PlayerStartVal;}
  
  void LogInfo();
private:
  int32 TeamID;
  FLinearColor TeamColor;

  int32 KillsNum = 0;
  int32 DeathsNum = 0;
  AKODPlayerStart* PlayerStart; 
};
