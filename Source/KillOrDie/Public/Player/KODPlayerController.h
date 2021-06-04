// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KODPlayerController.generated.h"

class UKODRespawnComponent;

UCLASS()
class KILLORDIE_API AKODPlayerController : public APlayerController {
  GENERATED_BODY()
public:
  AKODPlayerController();
protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UKODRespawnComponent* RespawnComponent;
};
