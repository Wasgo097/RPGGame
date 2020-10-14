// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "MyDamageTypes.generated.h"
UCLASS()
class RPGGAME_API UMyDamageTypes : public UDamageType{
	GENERATED_BODY()	
};
UCLASS()
class RPGGAME_API URestoreMana : public UMyDamageTypes {
	GENERATED_BODY()	
};
UCLASS()
class RPGGAME_API URestoreHealth : public UMyDamageTypes {
	GENERATED_BODY()	
};
UCLASS()
class RPGGAME_API UFireDamage : public UMyDamageTypes {
	GENERATED_BODY()	
};
UCLASS()
class RPGGAME_API UFrostDamage : public UMyDamageTypes {
	GENERATED_BODY()	
};
