// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KODMenuPlayerController.generated.h"

UCLASS()
class KILLORDIE_API AKODMenuPlayerController : public APlayerController {
  GENERATED_BODY()
public:
  virtual void BeginPlay() override;
};
