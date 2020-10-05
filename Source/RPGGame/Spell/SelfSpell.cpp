// Fill out your copyright notice in the Description page of Project Settings.
#include "SelfSpell.h"
#include "Kismet/GameplayStatics.h"
void USelfSpell::LevelUpSpell() {
	Super::LevelUpSpell();
	//if (SpellIsValid()) {
	if (ParticleEffect) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, GetOwner()->GetActorLocation());
	}
}
void USelfSpell::UseSpell() {
	Super::UseSpell();
}

