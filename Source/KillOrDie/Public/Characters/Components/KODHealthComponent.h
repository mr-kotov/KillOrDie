// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KODHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KILLORDIE_API UKODHealthComponent : public UActorComponent {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UKODHealthComponent();

  float GetHealth() const{return Health;}
  
protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  float MaxHealth = 100.0f;
  
  virtual void BeginPlay() override;

private:
  float Health = 0.0f;
};
