// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGGameCharacter.generated.h"
class ATargetSpell;
class UHealthComponent;
class UManaComponent;
UCLASS(config=Game)
class ARPGGameCharacter : public ACharacter{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	ARPGGameCharacter();
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Cast();
	void Attack();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void CameraForward(float Value);
	void Jump();
	void NextSpell();
	void PreviousSpell();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<ATargetSpell*> Spells;
	//UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	//	float Health = 1.0;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//	float Mana = 1.0;
	UPROPERTY(BlueprintReadOnly,Category="HP")
		UHealthComponent* HealthComp;
	UPROPERTY(BlueprintReadOnly, Category = "MP")
		UManaComponent* ManaComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool Casting1H =false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool AnyAction =false;
	FTimerHandle ActionHandle;
	int ActualSpell = 0;
};