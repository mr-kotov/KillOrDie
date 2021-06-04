// Kill or Die

#include "AI/KODAICharacter.h"


#include "BrainComponent.h"
#include "KDOAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/Components/KODAIWeaponComponent.h"

AKODAICharacter::AKODAICharacter(const FObjectInitializer& ObjInit):Super(
      ObjInit.SetDefaultSubobjectClass<UKODAIWeaponComponent>("WeaponComponent")) {
  AutoPossessAI = EAutoPossessAI::Disabled;
  AIControllerClass = AKDOAIController::StaticClass();

  bUseControllerRotationYaw = false;
  if(GetCharacterMovement()) {
    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
  }
}

void AKODAICharacter::OnDeath() {
  Super::OnDeath();

  const auto KODController = Cast<AAIController>(Controller);
  if(KODController && KODController->BrainComponent) {
    KODController->BrainComponent->Cleanup();
  }
}
