// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "BasicSpell.h"
#include "SelfSpell.generated.h"
class USelfSpellDataAsset;
UCLASS()
class RPGGAME_API ASelfSpell : public ABasicSpell{
	GENERATED_BODY()
public:
	virtual void UseSpell();
	virtual bool LevelUpSpell();
	virtual void InitSpell(int32 InLevel);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
		USelfSpellDataAsset* DataAsset;
};