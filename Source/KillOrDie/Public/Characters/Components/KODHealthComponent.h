// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KODCoreTypes.h"
#include "KODHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KILLORDIE_API UKODHealthComponent : public UActorComponent {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UKODHealthComponent();

  FOnDeath OnDeath;
  FOnHealthChanged OnHealthChanged;

  UFUNCTION(BlueprintCallable, Category = "Health")
  bool IsDead() const {return FMath::IsNearlyZero(Health);};

  UFUNCTION(BlueprintCallable, Category = "Health")
  float GetHealthPercent() const {return Health / MaxHealth;}
  
  float GetHealth() const{return Health;}

protected:
  /**Максимальное здоровье*/
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
  float MaxHealth = 100.0f;

  /**Работает ли авто восстановление здороья*/
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
  bool AutoHeal = false;

  /**Уровень восстановления здоровья за такт восстановления*/
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (ClampMin = "1.0", ClampMax = "30.0", EditCondition = "AutoHeal"))
  float HealAmount = 5.0f;

  /**Пауза перед стартом выполнения восстановления*/
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (ClampMin = "1.0", ClampMax = "100.0", EditCondition = "AutoHeal"))
  float HealDelay = 1.0f;

  /**Частота восстановления здоровья*/
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (ClampMin = "0.001", ClampMax = "30.0", EditCondition = "AutoHeal"))
  float HealUpdateFrequency = 2.0f;
  
  
  virtual void BeginPlay() override;

private:
  float Health = 0.0f;
    
  FTimerHandle HealTimerHandle;
  
  UFUNCTION()
  void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
  void OnTimerRecoveryHealth();
  void OnTimerRecoveryHealthEnd();
  void SetHealth(float NewHealth);
};
