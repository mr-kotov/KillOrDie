// Kill or Die

#include "Weapons/Animations/KODEquipFinishedAnimNotify.h"

void UKODEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation) {
  OnNotified.Broadcast(MeshComp);
  Super::Notify(MeshComp, Animation);
}
