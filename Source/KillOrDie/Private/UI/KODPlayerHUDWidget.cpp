// Kill or Die

#include "UI/KODPlayerHUDWidget.h"
#include "Weapons/Components/KODWeaponComponent.h"
#include "KODUtils.h"
#include "Components/ProgressBar.h" 
#include "Characters/Components/KODHealthComponent.h"

float UKODPlayerHUDWidget::GetHealthPercent() const {
  const auto HealthComponent = KODUtils::GetKODPlayerComponent<UKODHealthComponent>(GetOwningPlayerPawn());
  if(!HealthComponent) return 0.0f;

  return HealthComponent->GetHealthPercent();
}

bool UKODPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const {
  const auto WeaponComponent = KODUtils::GetKODPlayerComponent<UKODWeaponComponent>(GetOwningPlayerPawn());
  if(!WeaponComponent) return false;

  return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UKODPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const {
  const auto WeaponComponent = KODUtils::GetKODPlayerComponent<UKODWeaponComponent>(GetOwningPlayerPawn());
  if(!WeaponComponent) return false;

  return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool UKODPlayerHUDWidget::IsPlayerAlive() const {
  const auto HealthComponent = KODUtils::GetKODPlayerComponent<UKODHealthComponent>(GetOwningPlayerPawn());
  return HealthComponent && !HealthComponent->IsDead();
}

bool UKODPlayerHUDWidget::IsPlayerSpectating() const {
  const auto Controller = GetOwningPlayer();
  return Controller && Controller->GetStateName() == NAME_Spectating;
}

void UKODPlayerHUDWidget::NativeOnInitialized() {
  Super::NativeOnInitialized();
  
  if(GetOwningPlayer()) {
    GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UKODPlayerHUDWidget::OnNewPawn);
    OnNewPawn(GetOwningPlayerPawn());
  }
}

void UKODPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta) {
  if(HealthDelta < 0.0f) {
    OnTakeDamage();

    if(!IsAnimationPlaying(DamageAnimation)) {
      PlayAnimation(DamageAnimation);
    }
  }
  UpdateHealthBar();
}
  
void UKODPlayerHUDWidget::OnNewPawn(APawn* NewPawn) {
  const auto HealthComponent = KODUtils::GetKODPlayerComponent<UKODHealthComponent>(NewPawn);
  if(HealthComponent) {
    HealthComponent->OnHealthChanged.AddUObject(this, &UKODPlayerHUDWidget::OnHealthChanged);
  }
  UpdateHealthBar();
}

void UKODPlayerHUDWidget::UpdateHealthBar() {
  if(HealthProgressBar) {
    HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
  }
}

int32 UKODPlayerHUDWidget::GetKillsNum() const {
  const auto Controller = GetOwningPlayer();
  if(!Controller) return 0;

  const auto PlayerState = Cast<AKODPlayerState>(Controller->PlayerState);
  return  PlayerState ? PlayerState->GetKillsNum() : 0;
}

FString UKODPlayerHUDWidget::FormatBullets(int32 BulletsNum) const {
  const int32 MaxLen = 3;
  const TCHAR PrefixSymbol = '0';

  auto BulletStr = FString::FromInt(BulletsNum);
  const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

  if (SymbolsNumToAdd > 0)
  {
    BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
  }

  return BulletStr;
}
