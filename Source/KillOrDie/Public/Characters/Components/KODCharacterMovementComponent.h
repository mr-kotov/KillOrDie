// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KODCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class KILLORDIE_API UKODCharacterMovementComponent
    : public UCharacterMovementComponent {
  GENERATED_BODY()

public:
      UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement", meta = (ClampMin = "1.5", ClampMax = "10"))
      float RunModifier = 2.0f;
      
      virtual float GetMaxSpeed() const override;
};
