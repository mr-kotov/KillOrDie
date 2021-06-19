// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KODBaseCharacter.generated.h"


class UKODHealthComponent;
class UKODWeaponComponent;
class USoundCue;

UCLASS()
class KILLORDIE_API AKODBaseCharacter : public ACharacter {
  GENERATED_BODY()

public:
  AKODBaseCharacter(const FObjectInitializer& ObjInitializer);
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Run")
  float RunSpeed = 800.0f;

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  UKODHealthComponent* HealthComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  UKODWeaponComponent* WeaponComponent;
  
  UPROPERTY(EditDefaultsOnly, Category="Animations")
  UAnimMontage* DeathAnimMontage;

  UPROPERTY(EditDefaultsOnly, Category="Damage")
  float LifeSpanOnDeath = 5.0f;
  
  //Предельная скорость при которой будет наноситься урон
  UPROPERTY(EditDefaultsOnly, Category="Damage")
  FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

  UPROPERTY(EditDefaultsOnly, Category="Damage")
  FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

  UPROPERTY(EditDefaultsOnly, Category="Material")
  FName MaterialColorName = "Paint Color";

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
  USoundCue* DeathSound;
  
  virtual void BeginPlay() override;
  virtual void OnDeath();
  virtual void OnHealthChanged(float Health, float HealthDelta);
  
public:
  virtual void Tick(float DeltaTime) override;

  UFUNCTION(BlueprintCallable,  Category="Movement")
  virtual bool IsRunning() const;

  UFUNCTION(BlueprintCallable,  Category="Movement")
  float GetMovementDirection() const;

  void SetPlayerColor(const FLinearColor& Color);
  
private:
  UFUNCTION()
  void OnGroundLanded(const FHitResult& Hit);
};
