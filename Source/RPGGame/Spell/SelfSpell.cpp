// Fill out your copyright notice in the Description page of Project Settings.
#include "SelfSpell.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "DataAsset/SelfSpellDataAsset.h"
bool ASelfSpell::LevelUpSpell(){
	return Super::LevelUpSpell();
}
void ASelfSpell::InitSpell(int32 InLevel){
	Super::InitSpell(InLevel);
	Damage = DataAsset->DamagePerLevel;
	IsValid = IsValid && Damage > 0.0;
}
void ASelfSpell::UseSpell(){
	Super::UseSpell();
	if (SpellIsValid()) {
		if (ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, MyCharacter->GetActorLocation());
			UGameplayStatics::ApplyDamage(MyCharacter, Level*Damage, nullptr, MyCharacter, DamageType);
		}
	}
}