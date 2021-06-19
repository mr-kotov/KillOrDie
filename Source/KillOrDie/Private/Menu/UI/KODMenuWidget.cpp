// Kill or Die

#include "Menu/UI/KODMenuWidget.h"


#include "KODGameInstance.h"
#include "KODLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogUKODMenuWidget, All, All);

void UKODMenuWidget::NativeOnInitialized() {
  Super::NativeOnInitialized();

  if(StartGameButton) {
    StartGameButton->OnClicked.AddDynamic(this, &UKODMenuWidget::OnStartGame);
  }

  if(QuitGameButton) {
    QuitGameButton->OnClicked.AddDynamic(this, &UKODMenuWidget::OnQuitGame);
  }

  InitLevelItems();
}

void UKODMenuWidget::OnAnimationFinished_Implementation(
    const UWidgetAnimation* Animation) {
  if(Animation != HideAnimation) return;
  
  const auto KODGameInstance = GetKODGameInstance();
  if(!KODGameInstance) return;
  
  UGameplayStatics::OpenLevel(this, KODGameInstance->GetStartupLevel().LevelName);
}

void UKODMenuWidget::OnStartGame() {
  PlayAnimation(HideAnimation);
  UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void UKODMenuWidget::OnQuitGame() {
  UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UKODMenuWidget::InitLevelItems() {
  const auto KODGameInstance = GetKODGameInstance();
  if(!KODGameInstance) return;

  checkf(KODGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));
  if(!LevelItemBox) return;

  LevelItemBox->ClearChildren();

  for (auto LevelData: KODGameInstance->GetLevelsData()) {
    const auto LevelItemWidget = CreateWidget<UKODLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
    if(!LevelItemWidget) continue;

    LevelItemWidget->SetLevelData(LevelData);
    LevelItemWidget->OnLevelSelected.AddUObject(this, &UKODMenuWidget::OnLevelSelected);

    LevelItemBox->AddChild(LevelItemWidget);
    LevelItemWidgets.Add(LevelItemWidget);
  }

  if(KODGameInstance->GetStartupLevel().LevelName.IsNone()) {
    OnLevelSelected(KODGameInstance->GetLevelsData()[0]);
  }else {
    OnLevelSelected(KODGameInstance->GetStartupLevel());
  }
}

void UKODMenuWidget::OnLevelSelected(const FLevelData& Data) {
  const auto KODGameInstance = GetKODGameInstance();
  if(!KODGameInstance) return;

  KODGameInstance->SetStartupLevel(Data);

  for (auto LevelItemWidget: LevelItemWidgets) {
    if(LevelItemWidget) {
      //проверка по имени, если будут одинаковые имена в уровнях нужно будет добавлять id и по ним сравнивать
      const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
      LevelItemWidget->SetSelected(IsSelected);
    }
  }
}

UKODGameInstance* UKODMenuWidget::GetKODGameInstance() const {
  if(!GetWorld()) return nullptr;
  return GetWorld()->GetGameInstance<UKODGameInstance>();
}
