// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KODCoreTypes.h"
#include "KODHealthComponent.generated.h"

class UCameraShakeBase;
class UPhysicalMaterial;

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
  
  bool TryToAddHealthCond(float PickupHealAmount);
  bool IsHealthFull() const;
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

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  TSubclassOf<UCameraShakeBase> CameraShake;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
  TMap<UPhysicalMaterial*, float> DamageModifiers;
  
  virtual void BeginPlay() override;

private:
  float Health = 0.0f;
    
  FTimerHandle HealTimerHandle;
  
  UFUNCTION()
  void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

  UFUNCTION()
  void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

  UFUNCTION()
  void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);
  
  void OnTimerRecoveryHealth();
  void OnTimerRecoveryHealthEnd();
  void SetHealth(float NewHealth);

  void PlayCameraShake();
  void Killed(AController* KillerController);
  void ApplyDamage(float Damage, AController* InstigatedBy);
  float GetPointDamageModifier(AActor* DamageActor, const FName& BoneName);
};
