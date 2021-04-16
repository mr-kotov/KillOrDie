// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KODHealthComponent.generated.h"

//оповещение умерли или нет
DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KILLORDIE_API UKODHealthComponent : public UActorComponent {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UKODHealthComponent();

  float GetHealth() const{return Health;}

  UFUNCTION(BlueprintCallable)
  bool IsDead() const {return Health <= 0.0f;};

  FOnDeath OnDeath;
  FOnHealthChanged OnHealthChanged;
  
protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
  float MaxHealth = 100.0f;
  
  virtual void BeginPlay() override;

private:
  float Health = 0.0f;

  UFUNCTION()
  void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
