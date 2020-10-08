// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGGAME_API UHealthComponent : public UActorComponent{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UHealthComponent();
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintPure)
		float GetRatio();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
protected:
	UPROPERTY(BlueprintReadOnly,Category="Health")
		float ActualHealth=100.0;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Health")
		float MaxHealth=100.0;
	UFUNCTION()
		void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
