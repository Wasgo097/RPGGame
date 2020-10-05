// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "BasicSpell.h"
#include "TargetSpell.generated.h"
UCLASS()
class RPGGAME_API UTargetSpell : public UBasicSpell{
	GENERATED_BODY()
public:
	virtual void UseSpell();
	virtual void LevelUpSpell();
};
