// Copyright Epic Games, Inc. All Rights Reserved.
#include "RPGGameCharacter.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
/////
#include "ManaComponent.h"
#include "HealthComponent.h"
#include "../Spell/BasicSpell.h"
#define debug 1
ARPGGameCharacter::ARPGGameCharacter(){
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AirControl = 0.2f;
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	HealthComponent = CreateDefaultSubobject< UHealthComponent>(TEXT("HealthComponent"));
	ManaComponent = CreateDefaultSubobject<UManaComponent>(TEXT("ManaComponent"));
}
void ARPGGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent){
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARPGGameCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("CastSpell", IE_Pressed, this, &ARPGGameCharacter::Cast);
	PlayerInputComponent->BindAction("NextSpell", IE_Pressed, this, &ARPGGameCharacter::NextSpell);
	PlayerInputComponent->BindAction("PreviousSpell", IE_Pressed, this, &ARPGGameCharacter::PreviousSpell);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARPGGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPGGameCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("CameraForward", this, &ARPGGameCharacter::CameraForward);
}
void ARPGGameCharacter::BeginPlay(){
	Super::BeginPlay();
	FVector Location = GetMesh()->GetSocketLocation(TEXT("RightHandSocket"));
#if debug
	//DrawDebugSphere(GetWorld(), Location, 5.0, 12, FColor::Green, false, 10.0, 0, 1.0);
#endif
	for (TSubclassOf<ABasicSpell> Spell : AvailableSpells) {
		ABasicSpell* ACurrentSpell = GetWorld()->SpawnActor<ABasicSpell>(Spell,Location,FRotator::ZeroRotator);
		ACurrentSpell->InitSpell(1);
		FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
		ACurrentSpell->AttachToComponent(GetMesh(), Rules, TEXT("RightHandSocket"));
		Spells.Add(ACurrentSpell);
#if debug
		/*auto test = ACurrentSpell->GetAttachParentSocketName();
		UE_LOG(LogTemp, Display, TEXT("Socket: %s"), *test.ToString());*/
		//DrawDebugSphere(GetWorld(), ACurrentSpell->GetActorLocation(), 4.0, 12, FColor::Yellow, false, 5.0, 0, 1.0);
		UE_LOG(LogTemp, Display, TEXT("Location %s"), *ACurrentSpell->GetActorLocation().ToString());
#endif
	}
}
void ARPGGameCharacter::Cast(){
	if (!AnyAction && !GetWorld()->GetTimerManager().IsTimerActive(ActionHandle) &&!GetMovementComponent()->IsFalling() && ManaComponent->CastIsPossible(Spells[CurrentSpell]->GetRequirement())&& Spells[CurrentSpell]->SpellIsValid()){
		Casting1H = true;
		AnyAction = true;
		GetWorld()->GetTimerManager().SetTimer(ActionHandle, [this]() {
			Casting1H = false;
			AnyAction = false;
#if debug
			UE_LOG(LogTemp, Display, TEXT("Unblock"));
#endif
			}, 1.7, false);
#if debug
		UE_LOG(LogTemp, Display, TEXT("Block"));
#endif
		ManaComponent->Cast(Spells[CurrentSpell]->GetRequirement());
		Spells[CurrentSpell]->UseSpell();
	}
}
void ARPGGameCharacter::Attack(){
}
void ARPGGameCharacter::MoveForward(float Value){
	if ((Controller != NULL) && (Value != 0.0f)&&!GetMovementComponent()->IsFalling()&&!AnyAction){
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
void ARPGGameCharacter::MoveRight(float Value){
	if ( (Controller != NULL) && (Value != 0.0f) &&!GetMovementComponent()->IsFalling()&&!AnyAction){
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
void ARPGGameCharacter::CameraForward(float Value){
	float Scale = 25.0;
	float Distance = CameraBoom->TargetArmLength;
	//forward
	if (Value > 0.0&&Distance>=150.0f)
		Distance -= Value * Scale;
	//backward
	else if (Value < 0.0 && Distance <= 300.0f)
		Distance -= Value * Scale;
	CameraBoom->TargetArmLength = Distance;
}
void ARPGGameCharacter::Jump(){
	if (!AnyAction)
		Super::Jump();
}
void ARPGGameCharacter::NextSpell(){
	if (CurrentSpell < 6) {
		CurrentSpell++;
#if debug
		UE_LOG(LogTemp, Display, TEXT("Current Spell is %d %s"), CurrentSpell, *Spells[CurrentSpell]->GetFName().ToString());
#endif
	}
}
void ARPGGameCharacter::PreviousSpell(){
	if (CurrentSpell > 0) {
		CurrentSpell--;
#if debug
		UE_LOG(LogTemp, Display, TEXT("Current Spell is %d %s"), CurrentSpell, *Spells[CurrentSpell]->GetFName().ToString());
#endif
	}
}
float ARPGGameCharacter::HPRatio(){
	return HealthComponent->GetRatio();
}
float ARPGGameCharacter::MPRatio(){
	return ManaComponent->GetRatio();
}