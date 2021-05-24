// Kill or Die

#include "AI/KODAICharacter.h"

#include "KDOAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AKODAICharacter::AKODAICharacter(const FObjectInitializer& ObjInit):Super(ObjInit) {
  AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
  AIControllerClass = AKDOAIController::StaticClass();

  bUseControllerRotationYaw = false;
  if(GetCharacterMovement()) {
    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
  }
}
