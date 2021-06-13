// Kill or Die

#include "AI/KODAICharacter.h"


#include "BrainComponent.h"
#include "KDOAIController.h"
#include "KODHealthBarWidget.h"
#include "KODHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/Components/KODAIWeaponComponent.h"
#include "Components/WidgetComponent.h"

void AKODAICharacter::BeginPlay() {
  Super::BeginPlay();

  check(HealthWidgetComponent);
}

void AKODAICharacter::Tick(float DeltaSeconds) {
  Super::Tick(DeltaSeconds);

  UpdateHealthWidgetVisibility();
}

AKODAICharacter::AKODAICharacter(const FObjectInitializer& ObjInit):Super(
      ObjInit.SetDefaultSubobjectClass<UKODAIWeaponComponent>("WeaponComponent")) {
  AutoPossessAI = EAutoPossessAI::Disabled;
  AIControllerClass = AKDOAIController::StaticClass();

  bUseControllerRotationYaw = false;
  if(GetCharacterMovement()) {
    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
  }

  HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
  HealthWidgetComponent->SetupAttachment(GetRootComponent());
  HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
  HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AKODAICharacter::OnDeath() {
  Super::OnDeath();

  const auto KODController = Cast<AAIController>(Controller);
  if(KODController && KODController->BrainComponent) {
    KODController->BrainComponent->Cleanup();
  }
}

void AKODAICharacter::OnHealthChanged(float Health, float HealthDelta) {
  Super::OnHealthChanged(Health, HealthDelta);

  const auto HealthBarWidget = Cast<UKODHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
  if(!HealthBarWidget) return;
  HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void AKODAICharacter::UpdateHealthWidgetVisibility() {
  if(!GetWorld() || 
    !GetWorld()->GetFirstPlayerController() || 
    !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
    return;
  
  const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
  const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
  HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}
