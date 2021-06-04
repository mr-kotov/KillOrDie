// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KODRespawnComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KILLORDIE_API UKODRespawnComponent : public UActorComponent {
  GENERATED_BODY()

public:
  UKODRespawnComponent();

  void Respawn(int32 RespawnTime);
  int32 GetRespawnCountDown() const {return RespawnCountDown;}
  bool IsRespawnInProgress() const;
private:
  FTimerHandle RespawnTimerHandle;
  int32 RespawnCountDown = 0;
  void RespawnTimerUpdate();
};
