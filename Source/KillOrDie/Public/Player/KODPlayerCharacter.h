// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "KODBaseCharacter.h"
#include "GameFramework/Character.h"
#include "KODPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class KILLORDIE_API AKODPlayerCharacter : public AKODBaseCharacter {
  GENERATED_BODY()

public:
  AKODPlayerCharacter(const FObjectInitializer& ObjInitializer);

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  UCameraComponent* CameraComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  USpringArmComponent* SpringArmComponent;
  
  virtual void OnDeath() override;
  
public:
  virtual void SetupPlayerInputComponent(
    class UInputComponent* PlayerInputComponent) override;
    
   virtual bool IsRunning() const override;
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
