// Kill or Die

#include "AI/Services/KODFireService.h"

#include "AIController.h"
#include "KODUtils.h"
#include "KODWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UKODFireService::UKODFireService() {
  NodeName = "Fire";
}

void UKODFireService::TickNode(UBehaviorTreeComponent& OwnerComp,
    uint8* NodeMemory, float DeltaSeconds) {
  const auto Controller = OwnerComp.GetAIOwner();
  const auto Blackboard = OwnerComp.GetBlackboardComponent();
  const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
  if(Controller) {
    const auto WeaponComponent = KODUtils::GetKODPlayerComponent<UKODWeaponComponent>(Controller->GetPawn());
    if(WeaponComponent) {
      if(HasAim && LetShoot) {
        auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName));
        if(CenterActor) {
          auto EnemyLocation = CenterActor->GetActorLocation();
          const auto Pawn = Controller->GetPawn();
          if(Pawn) {
            const auto AILocation = Pawn->GetActorLocation().GetSafeNormal();
            const auto Direction = Pawn->GetActorForwardVector().GetSafeNormal();
            auto AIDirection = AILocation + Direction;
            auto EnemyDirection = EnemyLocation + Direction;            
            float Angle = FMath::Acos(FVector::DotProduct(AIDirection, EnemyDirection));
            Angle == 0 ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
          }
        }
      }else {
        WeaponComponent->StopFire();
      }
    }
  }
  
  Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
