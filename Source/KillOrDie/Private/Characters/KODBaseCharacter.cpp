// Kill or Die

#include "Characters/KODBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AKODBaseCharacter::AKODBaseCharacter() {
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
  SpringArmComponent->SetupAttachment(GetRootComponent());
  SpringArmComponent->bUsePawnControlRotation = true;
  
  CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
  CameraComponent->SetupAttachment(SpringArmComponent);  
}

// Called when the game starts or when spawned
void AKODBaseCharacter::BeginPlay() {
  Super::BeginPlay();

}

// Called every frame
void AKODBaseCharacter::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKODBaseCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  
  PlayerInputComponent->BindAxis("MoveForward", this, &AKODBaseCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this, &AKODBaseCharacter::MoveRight);

  PlayerInputComponent->BindAxis("LookUp", this, &AKODBaseCharacter::LookUp);
  PlayerInputComponent->BindAxis("TurnAround", this, &AKODBaseCharacter::TurnAround);
}

void AKODBaseCharacter::MoveForward(float Amount) {
  AddMovementInput(GetActorForwardVector(), Amount);
}

void AKODBaseCharacter::MoveRight(float Amount) {
  AddMovementInput(GetActorRightVector(), Amount);
}

void AKODBaseCharacter::LookUp(float Amount) {
  AddControllerPitchInput(Amount);
}

void AKODBaseCharacter::TurnAround(float Amount) {
  AddControllerYawInput(Amount);
}
