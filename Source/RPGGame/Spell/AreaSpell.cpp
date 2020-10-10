// Fill out your copyright notice in the Description page of Project Settings.
#include "AreaSpell.h"
#include "Kismet/GameplayStatics.h"
#include "AreaSpellDataAsset.h"
void AAreaSpell::LevelUpSpell(){
	Super::LevelUpSpell();
}
bool AAreaSpell::SpellIsValid(){
	return Super::SpellIsValid() && SphereCollision != nullptr;
}
void AAreaSpell::UseSpell(){
	Super::UseSpell();
}