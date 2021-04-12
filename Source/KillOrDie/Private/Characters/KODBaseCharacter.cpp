// Kill or Die

#include "Characters/KODBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Characters/Components/KODCharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
//SetDefaultSubobjectClass шаблонная функция принимает в качестве параметра шаблон класса подобъекта которым мы хотим заменить, в данном сулчае UKODCharacterMovementComponent
//в качестве параметра принимается наименование компонента 
AKODBaseCharacter::AKODBaseCharacter(const FObjectInitializer& ObjInitializer)
  : Super(
      ObjInitializer.SetDefaultSubobjectClass<UKODCharacterMovementComponent>(
          ACharacter::CharacterMovementComponentName)) {
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(
      "SpringArmComponent");
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

  PlayerInputComponent->BindAxis("MoveForward", this,
                                 &AKODBaseCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this,
                                 &AKODBaseCharacter::MoveRight);
  PlayerInputComponent->BindAxis("LookUp", this, &AKODBaseCharacter::LookUp);
  PlayerInputComponent->BindAxis("TurnAround", this,
                                 &AKODBaseCharacter::TurnAround);
  PlayerInputComponent->BindAction("Jump", IE_Pressed, this,
                                   &AKODBaseCharacter::Jump);
  PlayerInputComponent->BindAction("Run", IE_Pressed, this,
                                   &AKODBaseCharacter::OnStartRunning);
  PlayerInputComponent->BindAction("Run", IE_Released, this,
                                   &AKODBaseCharacter::OnStopRunning);
}

bool AKODBaseCharacter::IsRunning() const {
  return IsMovingForward && WantsToRun && !GetVelocity().IsZero();
}


void AKODBaseCharacter::MoveForward(float Amount) {
  AddMovementInput(GetActorForwardVector(), Amount);
  IsMovingForward = Amount > 0.0f;
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

void AKODBaseCharacter::OnStartRunning() {
  WantsToRun = true;
}

void AKODBaseCharacter::OnStopRunning() {
  WantsToRun = false;
}
