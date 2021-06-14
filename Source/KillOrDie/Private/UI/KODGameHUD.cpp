// Kill or Die

#include "UI/KODGameHUD.h"


#include "KODBaseWidget.h"
#include "KODGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

DEFINE_LOG_CATEGORY_STATIC(LogKODGameHUD, All, All);

void AKODGameHUD::DrawHUD() {
  Super::DrawHUD();
  //DrawCrossHair();
}

void AKODGameHUD::BeginPlay() {
  Super::BeginPlay();

  GameWidgets.Add(EKODMatchState::InProgress, CreateWidget<UKODBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
  GameWidgets.Add(EKODMatchState::Pause, CreateWidget<UKODBaseWidget>(GetWorld(), PauseWidgetClass));
  GameWidgets.Add(EKODMatchState::GameOver, CreateWidget<UKODBaseWidget>(GetWorld(), GameOverWidgetClass));

  for (auto GameWidgetPair: GameWidgets) {
    const auto GameWidget = GameWidgetPair.Value;
    if(!GameWidget) continue;

    GameWidget->AddToViewport();
    GameWidget->SetVisibility(ESlateVisibility::Hidden);
  }
  
  if(GetWorld()) {
    const auto GameMode = Cast<AKODGameModeBase>(GetWorld()->GetAuthGameMode());
    if(GameMode) {
      GameMode->OnMatchStateChanged.AddUObject(this, &AKODGameHUD::OnMatchStateChanged);
    }
  }
}

void AKODGameHUD::DrawCrossHair() {
  const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

  const float HalfLineSize = 10.0f;
  const float LineThickness = 2.0f;
  const FLinearColor LinearColor = FLinearColor::Green;
  
  DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LinearColor, LineThickness);
  DrawLine(Center.Min, Center.Max-HalfLineSize, Center.Min, Center.Max+HalfLineSize, LinearColor, LineThickness);
}

void AKODGameHUD::OnMatchStateChanged(EKODMatchState State) {
  if(CurrentWidget) {
    CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
  }

  if(GameWidgets.Contains(State)) {
    CurrentWidget = GameWidgets[State];
  }
  
  if(CurrentWidget) {
    CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    CurrentWidget->Show();
  }
}
