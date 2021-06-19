// Kill or Die

#include "Sound/KODSoundFuncLib.h"

#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogSoundFuncLib, All, All);

void UKODSoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass,
                                           float Volume) {
  if(!SoundClass) return;
  SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
  UE_LOG(LogSoundFuncLib, Display, TEXT("Sound class volume was changed: %s = %f"), *SoundClass->GetName(), SoundClass->Properties.Volume);
}

void UKODSoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass) {
  if(!SoundClass) return;

  const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
  SetSoundClassVolume(SoundClass, NextVolume);
}
