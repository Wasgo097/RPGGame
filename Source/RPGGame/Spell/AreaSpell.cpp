// Fill out your copyright notice in the Description page of Project Settings.
#include "AreaSpell.h"
#include "DataAsset/AreaSpellDataAsset.h"
#include "../Character/RPGGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#define debug 1
bool AAreaSpell::LevelUpSpell(){
	return Super::LevelUpSpell();
}
bool AAreaSpell::SpellIsValid(){
	return Super::SpellIsValid() && SphereCollision != nullptr;
}
void AAreaSpell::InitSpell(int32 InLevel){
	Super::InitSpell(InLevel);
	Damage = DataAsset->DamagePerLevel;
	IsValid = IsValid && Damage > 0.0&&ParticleManager!=nullptr&&SphereCollision!=nullptr;
	SphereCollision->SetSphereRadius(DataAsset->Range);
	ParticleManager->SetTemplate(ParticleEffect);
	DeactiveParticle();
}
void AAreaSpell::DeactiveParticle(){
	ParticleManager->Deactivate();
}
void AAreaSpell::UseSpell(){
	Super::UseSpell();
	if (ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
		TArray<AActor*> ActorsInRange;
		SphereCollision->GetOverlappingActors(ActorsInRange);
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, MyCharacter->GetActorLocation());
		ParticleManager->Activate();
		for (auto& Actor : ActorsInRange) {
			if (Actor == MyCharacter)
#if debug
#else
				continue;
#endif
			UGameplayStatics::ApplyDamage(Actor, Damage, nullptr, MyCharacter, DamageType);
		}
		GetWorld()->GetTimerManager().SetTimer(ParticleTimer, this, &AAreaSpell::DeactiveParticle,3.0, false);
	}
}
AAreaSpell::AAreaSpell() {
	SphereCollision = CreateDefaultSubobject< USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
	ParticleManager = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleManager"));
	ParticleManager->SetupAttachment(RootComponent);
}