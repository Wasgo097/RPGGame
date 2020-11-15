// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicSpell.generated.h"
class UParticleSystem;
class UDamageType;
class USceneComponent;
UCLASS()
class RPGGAME_API ABasicSpell : public AActor{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ABasicSpell();
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	virtual bool SpellIsValid();
	virtual void UseSpell();
	virtual bool LevelUpSpell();
	virtual void InitSpell(int32 InLevel);
	float GetRequirement() { return Requirement; }
	int32 GetLevel() { return Level; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly)
		USceneComponent* SceneComponent=nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
		UParticleSystem* ParticleEffect = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
		TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
		TMap<int32, float> ManaRequirementPerLevel;
	UPROPERTY(BlueprintReadOnly, Category = "Properties")
		float Requirement=0.0;
	UPROPERTY(BlueprintReadOnly, Category = "Properties")
		float Damage=0.0;
	UPROPERTY(BlueprintReadOnly, Category = "Properties")
		int32 Level=0;
	UPROPERTY(BlueprintReadOnly, Category = "Properties")
		bool IsValid = false;
};
