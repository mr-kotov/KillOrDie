// Kill or Die

#include "AI/KODAICharacter.h"

#include "KDOAIController.h"

AKODAICharacter::AKODAICharacter(const FObjectInitializer& ObjInit):Super(ObjInit) {
  AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
  AIControllerClass = AKDOAIController::StaticClass();
}
