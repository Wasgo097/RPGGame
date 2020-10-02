// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicSpell.generated.h"
class UDamageType;
class UParticleSystem;
class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class RPGGAME_API ABasicSpell : public AActor{
	GENERATED_BODY()	
public:	
	ABasicSpell(){
		PrimaryActorTick.bCanEverTick = true;
		Level = 0;
		Requirement = 0.0;
	}
	// Sets default values for this actor's properties
	ABasicSpell(int32 Level, float Requirement);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void UseSpell() {}
	virtual void LevelUpSpell(){}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(/*EditDefaultsOnly,*/ BlueprintReadOnly, Category = "Gameplay")
		UProjectileMovementComponent* MovementComp = nullptr;
	UPROPERTY(/*EditDefaultsOnly,*/ BlueprintReadOnly, Category = "Gameplay") 
		USphereComponent* SphereCollision=nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay") 
		UParticleSystem* ParticleEffect=nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
		TSubclassOf<UDamageType> DamageType;
	UPROPERTY(BlueprintReadOnly, Category = "Properties")
		float Requirement;
	UPROPERTY(BlueprintReadOnly, Category = "Properties")
		int32 Level;
};