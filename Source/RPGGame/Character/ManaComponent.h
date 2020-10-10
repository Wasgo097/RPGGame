// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ManaComponent.generated.h"
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGGAME_API UManaComponent : public UActorComponent{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UManaComponent();
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintPure)
		float GetRatio();
	bool CastIsPossible(float Requirement);
	void Cast(float Requirement);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "Mana")
		float ActualMana = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mana")
		float MaxMana = 100.0;
};
