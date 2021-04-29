// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "KODEquipFinishedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);

UCLASS()
class KILLORDIE_API UKODEquipFinishedAnimNotify : public UAnimNotify {
  GENERATED_BODY()

public:
  virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

  FOnNotifiedSignature OnNotified;
};
