// Kill or Die

#include "UI/KODPlayerStatRowWidget.h"


#include "Components/Image.h"
#include "Components/TextBlock.h"

void UKODPlayerStatRowWidget::SetPlayerName(const FText& Text) {
  if(!PlayerNameTextBlock) return;
  PlayerNameTextBlock->SetText(Text);
}

void UKODPlayerStatRowWidget::SetKills(const FText& Text) {
  if(!KillsTextBlock) return;
  KillsTextBlock->SetText(Text);
}

void UKODPlayerStatRowWidget::SetDeaths(const FText& Text) {
  if(!DeathsTextBlock) return;
  DeathsTextBlock->SetText(Text);
}

void UKODPlayerStatRowWidget::SetTeam(const FText& Text) {
  if(!TeamTextBlock) return;
  TeamTextBlock->SetText(Text);
}

void UKODPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible) {
  if(!PlayerIndicatorImage) return;
  PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UKODPlayerStatRowWidget::SetTeamColor(const FLinearColor& Color) {
  if(!TeamImage) return;
  TeamImage->SetColorAndOpacity(Color);
}
