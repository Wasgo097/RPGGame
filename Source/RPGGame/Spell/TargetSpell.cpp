// Fill out your copyright notice in the Description page of Project Settings.
#include "TargetSpell.h"
#include "Projectile/Projectile.h"
#include "DataAsset/TargetSpellDataAsset.h"
//
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#define debug 1
bool ATargetSpell::LevelUpSpell(){
	return Super::LevelUpSpell();
}
void ATargetSpell::InitSpell(int32 InLevel){
	Super::InitSpell(InLevel);
	Damage = DataAsset->DamagePerLevel;
	IsValid = IsValid && Damage > 0.0&&Projectile!=nullptr;
}
void ATargetSpell::UseSpell(){
	Super::UseSpell();
	if (SpellIsValid()) {
		if (ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
			//rotate character to target direction
			FVector Location;
			FRotator Rotator,CharacterRotator;
			APlayerController* PlayerController= MyCharacter->GetController<APlayerController>();
			PlayerController->GetPlayerViewPoint(Location, Rotator);
			CharacterRotator = Rotator;
			CharacterRotator.Roll = 0.0;
			CharacterRotator.Pitch = 0.0;
			MyCharacter->SetActorRotation(CharacterRotator);
			//Location = ;
			Location = GetActorLocation() + (Rotator.Vector() * 20);
#if debug
			FVector EndTrace = FVector::ZeroVector;
			EndTrace = Location + (Rotator.Vector() * 1000);
			DrawDebugLine(GetWorld(), Location, EndTrace, FColor::Red, false, 10.0, 0, 1.0);
#endif
			FActorSpawnParameters Parameters;
			Parameters.Owner = MyCharacter;
			Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			//Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AProjectile* CurrentProjectile=GetWorld()->SpawnActor<AProjectile>(Projectile,Location , Rotator, Parameters);
			CurrentProjectile->InitProjectile(DamageType, ParticleEffect, Level * Damage);
#if debug 
			UE_LOG(LogTemp, Display, TEXT("Spell casted"));
			DrawDebugSphere(GetWorld(), CurrentProjectile->GetActorLocation(), 2.0, 12, FColor::Green, false, 10.0, 0, 1.0);
			//UE_LOG(LogTemp, Display, TEXT("Spell casted rotation %s"),*CameraRotator.ToString());
			//UE_LOG(LogTemp, Display, TEXT("Character rotation %s"),*MyCharacter->GetActorRotation().ToString());
#endif
		}
	}
}