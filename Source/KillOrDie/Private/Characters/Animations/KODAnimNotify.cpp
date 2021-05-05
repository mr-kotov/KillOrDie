// Kill or Die

#include "Characters/Animations/KODAnimNotify.h"

void UKODAnimNotify::Notify(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation) {
  OnNotified.Broadcast(MeshComp);
  Super::Notify(MeshComp, Animation);
}
