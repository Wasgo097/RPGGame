// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "BasicSpell.h"
#include "AreaSpell.generated.h"
UCLASS()
class RPGGAME_API AAreaSpell : public ABasicSpell{
	GENERATED_BODY()
public:
	virtual void UseSpell();
	virtual void LevelUpSpell();
	virtual bool SpellIsValid();
};