// Kill or Die

#include "Menu/UI/KODLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UKODLevelItemWidget::SetLevelData(const FLevelData& Data) {
  LevelData = Data;

  if(LevelNameTextBlock) {
    LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
  }

  if(LevelImage) {
    LevelImage->SetBrushFromTexture(Data.LevelThumb);
  }
}

void UKODLevelItemWidget::SetSelected(bool IsSelected) {
  if(FrameImage) {
    FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
  }
}

void UKODLevelItemWidget::NativeOnInitialized() {
  Super::NativeOnInitialized();

  if(LevelSelectButton) {
    LevelSelectButton->OnClicked.AddDynamic(this, &UKODLevelItemWidget::OnLevelItemClicked);
  }
}

void UKODLevelItemWidget::OnLevelItemClicked() {
  OnLevelSelected.Broadcast(LevelData);
}
