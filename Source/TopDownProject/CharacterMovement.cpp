// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMovement.h"

// Sets default values
ACharacterMovement::ACharacterMovement()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//stop the controller to rotate //allow the camera to rotate
	//Rotation in XYZ Axis
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//rotate the character towards the direction he is moving
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	//how much can i control the character while in the air
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);// rootcomponent is capsulecomponent

	// how far the camera boom is going away from the palyer
	CameraBoom->TargetArmLength = 800.0f;
	// rotate the arm based on character controller
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera->bUsePawnControlRotation = false;

}


// Called when the game starts or when spawned
void ACharacterMovement::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);// X is Raw , Y is Pitch , Z is Yaw
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterMovement::Attack);


	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterMovement::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterMovement::MoveRight);
}

void ACharacterMovement::MoveForward(float Axis)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	//Get the Forward Direction Pitch
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); 

	//Axis from 1.0 to -1.0
	AddMovementInput(Direction, Axis);
}

void ACharacterMovement::MoveRight(float Axis)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	//Get the Forward Right Pitch
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//Axis from 1.0 to -1.0
	AddMovementInput(Direction, Axis);
}

void ACharacterMovement::Attack()
{
	isAttacking = true;
}

void ACharacterMovement::Att()
{
	isAttacking = false;
}
