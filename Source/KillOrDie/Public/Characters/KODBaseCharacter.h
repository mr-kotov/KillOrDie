// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KODBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UKODHealthComponent;
class UTextRenderComponent;
class AKODBaseWeapon;

UCLASS()
class KILLORDIE_API AKODBaseCharacter : public ACharacter {
  GENERATED_BODY()

public:
  AKODBaseCharacter(const FObjectInitializer& ObjInitializer);
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Run")
  float RunSpeed = 800.0f;

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  UCameraComponent* CameraComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  USpringArmComponent* SpringArmComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  UKODHealthComponent* HealthComponent;
  
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  UTextRenderComponent* HealthTextComponent;
  
  UPROPERTY(EditDefaultsOnly, Category="Animations")
  UAnimMontage* DeathAnimMontage;

  UPROPERTY(EditDefaultsOnly, Category="Damage")
  float LifeSpanOnDeath = 5.0f;
  
  //Предельная скорость при которой будет наноситься урон
  UPROPERTY(EditDefaultsOnly, Category="Damage")
  FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

  UPROPERTY(EditDefaultsOnly, Category="Damage")
  FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

  UPROPERTY(EditDefaultsOnly, Category="Weapon")
  TSubclassOf<AKODBaseWeapon> WeaponClass;
  
  virtual void BeginPlay() override;
  
  
public:
  virtual void Tick(float DeltaTime) override;

  virtual void SetupPlayerInputComponent(
      class UInputComponent* PlayerInputComponent) override;

  UFUNCTION(BlueprintCallable,  Category="Movement")
  bool IsRunning() const;

  UFUNCTION(BlueprintCallable,  Category="Movement")
  float GetMovementDirection() const;
  
private:
  bool WantsToRun = false;
  bool IsMovingForward = false;
  
  void MoveForward(float Amount);
  void MoveRight(float Amount);

  void LookUp(float Amount);
  void TurnAround(float Amount);
  void OnStartRunning();
  void OnStopRunning();

  void OnDeath();
  void OnHealthChanged(float Health);

  UFUNCTION()
  void OnGroundLanded(const FHitResult& Hit);
  
  void SpawnWeapon();  
};
