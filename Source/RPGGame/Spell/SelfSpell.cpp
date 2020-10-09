// Fill out your copyright notice in the Description page of Project Settings.
#include "SelfSpell.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
void ASelfSpell::LevelUpSpell(){
	Super::LevelUpSpell();
}
void ASelfSpell::UseSpell(){
	Super::UseSpell();
	if (SpellIsValid()) {
		if (ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, MyCharacter->GetActorLocation());
			UGameplayStatics::ApplyDamage(MyCharacter, 10, nullptr, MyCharacter, nullptr);
		}
	}
}