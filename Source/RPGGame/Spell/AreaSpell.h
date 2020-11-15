// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "BasicSpell.h"
#include "AreaSpell.generated.h"
class UAreaSpellDataAsset;
class USphereComponent;
class UParticleSystemComponent;
UCLASS()
class RPGGAME_API AAreaSpell : public ABasicSpell{
	GENERATED_BODY()
public:
	AAreaSpell();
	virtual void UseSpell();
	virtual bool LevelUpSpell();
	virtual bool SpellIsValid();
	virtual void InitSpell(int32 InLevel);
protected:
	UPROPERTY(BlueprintReadOnly)
		USphereComponent* SphereCollision = nullptr;
	UPROPERTY(EditDefaultsOnly,Category="Data")
		UAreaSpellDataAsset* DataAsset;
	UPROPERTY(BlueprintReadOnly)
		UParticleSystemComponent* ParticleManager = nullptr;
	UPROPERTY()
		FTimerHandle ParticleTimer;
protected:
	UFUNCTION()
		void DeactiveParticle();
};