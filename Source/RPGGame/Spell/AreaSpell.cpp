// Fill out your copyright notice in the Description page of Project Settings.
#include "AreaSpell.h"
#include "Kismet/GameplayStatics.h"
#include "DataAsset/AreaSpellDataAsset.h"
bool AAreaSpell::LevelUpSpell(){
	return Super::LevelUpSpell();
}
bool AAreaSpell::SpellIsValid(){
	return Super::SpellIsValid() && SphereCollision != nullptr;
}
void AAreaSpell::UseSpell(){
	Super::UseSpell();
}