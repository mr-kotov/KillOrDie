// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "KODPlayerStart.generated.h"

UCLASS()
class KILLORDIE_API AKODPlayerStart : public APlayerStart {
  GENERATED_BODY()

public:
  int32 GetTeamID() {return TeamID;}
  bool GetIsFree() {return IsFree;}
  void ToTake() { IsFree = false;}
  
protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (ClampMin = "1", ClampMax = "2"))
  int32 TeamID = 1;

private:
  bool IsFree = true;
};
