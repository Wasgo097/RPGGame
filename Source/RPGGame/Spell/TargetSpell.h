// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "BasicSpell.h"
#include "TargetSpell.generated.h"
class UTargetSpellDataAsset;
UCLASS()
class RPGGAME_API ATargetSpell : public ABasicSpell{
	GENERATED_BODY()
public:
	virtual void UseSpell();
	virtual void LevelUpSpell();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
		UTargetSpellDataAsset* DataAsset;
};