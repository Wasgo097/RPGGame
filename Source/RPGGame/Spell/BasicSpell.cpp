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
UBasicSpell::UBasicSpell(int32 Level) :Level{ Level }{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Requirement = ManaRequirementPerLevel[Level];
}
// Called every frame
//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
void UBasicSpell::UseSpell() {
	if (!SpellIsValid())
		UE_LOG(LogTemp, Warning, TEXT("Spell isn't valid %s"), *this->GetFName().ToString());
}
void UBasicSpell::LevelUpSpell() {}
// Called when the game starts
void UBasicSpell::BeginPlay(){
	Super::BeginPlay();
}
bool UBasicSpell::SpellIsValid(){
	return ManaRequirementPerLevel.Num() > 1 && Level > 0 && Requirement > 0 && ParticleEffect != nullptr;
}
// Called every frame
//void UBasicSpell::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}

