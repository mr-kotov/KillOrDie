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
  if(LevelImage) {
    LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
  }
}

void UKODLevelItemWidget::NativeOnInitialized() {
  Super::NativeOnInitialized();

  if(LevelSelectButton) {
    LevelSelectButton->OnClicked.AddDynamic(this, &UKODLevelItemWidget::OnLevelItemClicked);
    LevelSelectButton->OnHovered.AddDynamic(this, &UKODLevelItemWidget::OnLevelItemHovered);
    LevelSelectButton->OnUnhovered.AddDynamic(this, &UKODLevelItemWidget::OnLevelItemUnhovered);
  }
}

void UKODLevelItemWidget::OnLevelItemClicked() {
  OnLevelSelected.Broadcast(LevelData);
}

void UKODLevelItemWidget::OnLevelItemHovered() {
  if(FrameImage) {
    FrameImage->SetVisibility(ESlateVisibility::Visible);
  }
}

void UKODLevelItemWidget::OnLevelItemUnhovered() {
  if(FrameImage) {
    FrameImage->SetVisibility(ESlateVisibility::Hidden);
  }
}
