// Kill or Die

#include "Core/KODGameInstance.h"
#include "Sound/KODSoundFuncLib.h"

void UKODGameInstance::ToggleVolume() {
  UKODSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}
