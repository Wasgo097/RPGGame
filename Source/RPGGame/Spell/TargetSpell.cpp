// Fill out your copyright notice in the Description page of Project Settings.
#include "TargetSpell.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile/Projectile.h"
#include "DataAsset/TargetSpellDataAsset.h"
bool ATargetSpell::LevelUpSpell(){
	return Super::LevelUpSpell();
}
void ATargetSpell::UseSpell(){
	Super::UseSpell();
}