// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Characters/KODBaseCharacter.h"
#include "KODAICharacter.generated.h"

UCLASS()
class KILLORDIE_API AKODAICharacter : public AKODBaseCharacter {
  GENERATED_BODY()

public:
  AKODAICharacter(const FObjectInitializer& ObjInit);
};
