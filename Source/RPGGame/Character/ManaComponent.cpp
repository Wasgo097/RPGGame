// Fill out your copyright notice in the Description page of Project Settings.
#include "ManaComponent.h"
// Sets default values for this component's properties
UManaComponent::UManaComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UManaComponent::BeginPlay(){
	ActualMana = MaxMana;
	Super::BeginPlay();
}
float UManaComponent::GetRatio(){
	return ActualMana / MaxMana;
}
bool UManaComponent::CastIsPossible(float Requirement){
	return Requirement<= ActualMana;
}
void UManaComponent::Cast(float Requirement){
	if (CastIsPossible(Requirement))
		ActualMana -= Requirement;
}
// Called every frame
//void UManaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}

