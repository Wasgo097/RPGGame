// Fill out your copyright notice in the Description page of Project Settings.
#include "AreaSpell.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "DataAsset/AreaSpellDataAsset.h"
#include "../Character/RPGGameCharacter.h"
#define debug 1
bool AAreaSpell::LevelUpSpell(){
	return Super::LevelUpSpell();
}
bool AAreaSpell::SpellIsValid(){
	return Super::SpellIsValid() && SphereCollision != nullptr;
}
void AAreaSpell::InitSpell(int32 InLevel, float InDamage){
	Super::InitSpell(InLevel, InDamage);
	SphereCollision->SetSphereRadius(DataAsset->Range);
}
void AAreaSpell::UseSpell(){
	Super::UseSpell();
	if (ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
		TArray<AActor*> ActorsInRange;
		SphereCollision->GetOverlappingActors(ActorsInRange);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, MyCharacter->GetActorLocation());
		for (auto& Actor : ActorsInRange) {
			if (Actor==MyCharacter)
				continue;
			UGameplayStatics::ApplyDamage(Actor, Damage, nullptr, MyCharacter, DamageType);
		}
	}
}
AAreaSpell::AAreaSpell() {
	SphereCollision = CreateDefaultSubobject< USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
}