// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KODSoundFuncLib.generated.h"

class USoundClass;

UCLASS()
class KILLORDIE_API UKODSoundFuncLib : public UBlueprintFunctionLibrary {
  GENERATED_BODY()
public:
  UFUNCTION(BlueprintCallable)
  static void SetSoundClassVolume(USoundClass* SoundClass, float Volume);

  UFUNCTION(BlueprintCallable)
  static void ToggleSoundClassVolume(USoundClass* SoundClass);
};
