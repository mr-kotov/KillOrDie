// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "KODBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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
  
  virtual void BeginPlay() override;
  
public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      class UInputComponent* PlayerInputComponent) override;

  UFUNCTION(BlueprintCallable,  Category="Movement")
  bool IsRunning() const;
  
private:
  bool WantsToRun = false;
  bool IsMovingForward = false;
  
  void MoveForward(float Amount);
  void MoveRight(float Amount);

  void LookUp(float Amount);
  void TurnAround(float Amount);
  void OnStartRunning();
  void OnStopRunning();
};
