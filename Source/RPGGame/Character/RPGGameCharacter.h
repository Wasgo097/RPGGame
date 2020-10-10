// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGGameCharacter.generated.h"
class ABasicSpell;
class UHealthComponent;
class UManaComponent;
class ABasicSpell;
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
	virtual void BeginPlay();
	void Cast();
	void Attack();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void CameraForward(float Value);
	void Jump();
	void NextSpell();
	void PreviousSpell();
	UFUNCTION(BlueprintPure)
		float HPRatio();
	UFUNCTION(BlueprintPure)
		float MPRatio();
protected:
	UPROPERTY(EditInstanceOnly, Category = "Spell")
		TArray<TSubclassOf<ABasicSpell>> AvailableSpells;
	UPROPERTY(BlueprintReadOnly, Category = "Spell")
		TArray<ABasicSpell*> Spells;
	UPROPERTY(BlueprintReadOnly,Category="HP")
		UHealthComponent* HealthComponent;
	UPROPERTY(BlueprintReadOnly, Category = "MP")
		UManaComponent* ManaComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool Casting1H =false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool AnyAction =false;
	FTimerHandle ActionHandle;
	//index 0 is null
	int32 CurrentSpell = 1;
};