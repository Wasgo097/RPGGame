// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicSpell.generated.h"
class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystem;
class UDamageType;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGGAME_API UBasicSpell : public UActorComponent{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UBasicSpell();
	UBasicSpell(int32 Level);
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void UseSpell();
	virtual void LevelUpSpell();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//UPROPERTY(/*EditDefaultsOnly,*/ BlueprintReadOnly, Category = "Gameplay")
	//	UProjectileMovementComponent* MovementComp = nullptr;
	UPROPERTY(/*EditDefaultsOnly,*/ BlueprintReadOnly, Category = "Gameplay")
		USphereComponent* SphereCollision = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
		UParticleSystem* ParticleEffect = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
		TSubclassOf<UDamageType> DamageType;
	UPROPERTY(BlueprintReadOnly, Category = "Properties")
		float Requirement;
	UPROPERTY(BlueprintReadOnly, Category = "Properties")
		int32 Level;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
		TMap<int32, float> ManaRequirementPerLevel;
public:
	bool SpellIsValid();
};
