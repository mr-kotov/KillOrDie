// Kill or Die

#include "UI/KODGameOverWidget.h"
#include "KODGameModeBase.h"
#include "KODPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UKODGameOverWidget::NativeOnInitialized() {
  Super::NativeOnInitialized();
  
  if(GetWorld()) {
    const auto GameMode = Cast<AKODGameModeBase>(GetWorld()->GetAuthGameMode());
    if(GameMode) {
      GameMode->OnMatchStateChanged.AddUObject(this, &UKODGameOverWidget::OnMatchStateChanged);
    }
  }
  if(ResetLevelButton) {
    ResetLevelButton->OnClicked.AddDynamic(this, &UKODGameOverWidget::OnResetLevel);
  }
}

void UKODGameOverWidget::OnMatchStateChanged(EKODMatchState State) {
  if(State == EKODMatchState::GameOver) {
    UpdatePlayersStat();
  }
}

void UKODGameOverWidget::UpdatePlayersStat() {
  if(!GetWorld() || !PlayerStatBox) return;

  PlayerStatBox->ClearChildren();
  
  for (auto It = GetWorld()->GetControllerIterator(); It; ++It) {
    const auto Controller = It->Get();
    if(!Controller) continue;

    const auto PlayerState = Cast<AKODPlayerState>(Controller->PlayerState);
    if(!PlayerState) continue;

    const auto PlayerStatRowWidget = CreateWidget<UKODPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
    if(!PlayerStatRowWidget) continue;

    PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
    PlayerStatRowWidget->SetKills(KODUtils::TextFromInt(PlayerState->GetKillsNum()));
    PlayerStatRowWidget->SetDeaths(KODUtils::TextFromInt(PlayerState->GetDeathsNum()));
    PlayerStatRowWidget->SetTeam(KODUtils::TextFromInt(PlayerState->GetTeamID()));
    PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

    PlayerStatBox->AddChild(PlayerStatRowWidget);
  }
}

void UKODGameOverWidget::OnResetLevel() {
  const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
  UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
