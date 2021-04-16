// Kill or Die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KODBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UKODHealthComponent;
class UTextRenderComponent;

UCLASS()
class KILLORDIE_API AKODBaseCharacter : public ACharacter {
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
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
  
  virtual void BeginPlay() override;
  
  
public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
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
};
