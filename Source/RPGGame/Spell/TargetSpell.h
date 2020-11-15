// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "BasicSpell.h"
#include "TargetSpell.generated.h"
UCLASS()
class RPGGAME_API ATargetSpell : public ABasicSpell{
	GENERATED_BODY()
public:
	virtual void UseSpell();
	virtual bool LevelUpSpell();
	virtual void InitSpell(int32 InLevel);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
		class UTargetSpellDataAsset* DataAsset;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<class AProjectile> Projectile;
};