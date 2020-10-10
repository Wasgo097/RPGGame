// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AreaSpellDataAsset.generated.h"
UCLASS()
class RPGGAME_API UAreaSpellDataAsset : public UDataAsset{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 DamagePerLevel;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Range;
};
