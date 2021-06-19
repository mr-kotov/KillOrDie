// Kill or Die

#include "UI/KODBaseWidget.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void UKODBaseWidget::Show() {
  PlayAnimation(ShowAnimation);
  UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
}
