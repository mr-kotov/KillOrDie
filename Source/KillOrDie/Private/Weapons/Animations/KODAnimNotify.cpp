// Kill or Die

#include "Weapons/Animations/KODAnimNotify.h"

void UKODAnimNotify::Notify(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation) {
  OnNotified.Broadcast(MeshComp);
  Super::Notify(MeshComp, Animation);
}
