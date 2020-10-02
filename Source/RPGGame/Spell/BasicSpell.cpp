// Fill out your copyright notice in the Description page of Project Settings.
#include "BasicSpell.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/DamageType.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
ABasicSpell::ABasicSpell(int32 Level, float Requirement) :Level{ Level }, Requirement{ Requirement }{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void ABasicSpell::BeginPlay(){
	Super::BeginPlay();
}
// Called every frame
void ABasicSpell::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}