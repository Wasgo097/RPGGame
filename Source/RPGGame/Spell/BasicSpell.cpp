// Fill out your copyright notice in the Description page of Project Settings.
#include "BasicSpell.h"
#include "Particles/ParticleSystem.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
// Sets default values
ABasicSpell::ABasicSpell(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Level = 0;
	Requirement = 0.0f;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
}
// Called when the game starts or when spawned
void ABasicSpell::BeginPlay(){
	Super::BeginPlay();	
}
// Called every frame
//void ABasicSpell::Tick(float DeltaTime){
//	Super::Tick(DeltaTime);
//}
bool ABasicSpell::SpellIsValid(){
	return bIsValid;
}
void ABasicSpell::UseSpell(){
	if (!SpellIsValid())
		UE_LOG(LogTemp, Warning, TEXT("Spell isn't valid %s"), *this->GetFName().ToString());
}
bool ABasicSpell::LevelUpSpell(){
	if (ManaRequirementPerLevel.Contains(Level + 1)) {
		Level++;
		Requirement = ManaRequirementPerLevel[Level];
		return true;
	}
	return false;
}
void ABasicSpell::InitSpell(int32 NewLevel){
	this->Level = NewLevel;
	this->Requirement = ManaRequirementPerLevel[this->Level];
	bIsValid= ManaRequirementPerLevel.Num() > 0 && Level > 0 && Requirement > 0 && ParticleEffect != nullptr;
}

