// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicSpell.generated.h"
class ParticleSystem;
class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class RPGGAME_API ABasicSpell : public AActor
{
	GENERATED_BODY()	
public:	
	// Sets default values for this actor's properties
	ABasicSpell();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(/*EditDefaultsOnly,*/ BlueprintReadOnly, Category = "Gameplay")
		UProjectileMovementComponent* MovementComp = nullptr;
	UPROPERTY(/*EditDefaultsOnly,*/ BlueprintReadOnly, Category = "Gameplay") 
		USphereComponent* SphereCollision=nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay") 
		ParticleSystem* ParticleEffect=nullptr;
};
