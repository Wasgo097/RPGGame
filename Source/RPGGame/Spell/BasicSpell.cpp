// Fill out your copyright notice in the Description page of Project Settings.
#include "BasicSpell.h"
// Sets default values for this component's properties
UBasicSpell::UBasicSpell(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	Level = 0;
	Requirement = 0.0f;
	PrimaryComponentTick.bCanEverTick = true;
}
UBasicSpell::UBasicSpell(int32 Level, float Requirement) :Level{ Level }, Requirement{ Requirement } {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UBasicSpell::BeginPlay(){
	Super::BeginPlay();
}
// Called every frame
//void UBasicSpell::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}

