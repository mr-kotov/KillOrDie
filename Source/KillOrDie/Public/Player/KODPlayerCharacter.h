// Kill or Die

#pragma once

#include "CoreMinimal.h"

#include "KODBaseCharacter.h"
#include "GameFramework/Character.h"
#include "KODPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

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
  
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
  USphereComponent* CameraCollisionComponent;
  
  virtual void OnDeath() override;
  virtual void BeginPlay() override;
  
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

  UFUNCTION()
  void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
  UFUNCTION()
  void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

  void CheckCameraOverlap();
};
