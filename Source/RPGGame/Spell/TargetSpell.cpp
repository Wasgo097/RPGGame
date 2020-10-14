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
void ATargetSpell::UseSpell(){
	Super::UseSpell();
	if (SpellIsValid()) {
		if (ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
			FVector Location;
			FRotator Rotator;
			APlayerController* PlayerController= MyCharacter->GetController<APlayerController>();
			PlayerController->GetPlayerViewPoint(Location, Rotator);
			Rotator.Roll = 0.0;
			Rotator.Pitch = 0.0;
			MyCharacter->SetActorRotation(Rotator);
			Location = GetActorLocation();
#if debug
			FVector EndTrace = FVector::ZeroVector;
			EndTrace = Location + (Rotator.Vector() * 1000);
			DrawDebugLine(GetWorld(), Location, EndTrace, FColor::Red, false, 10.0, 0, 1.0);
#endif
			AProjectile* CurrentProjectile=GetWorld()->SpawnActor<AProjectile>(Projectile,Location , Rotator);
			CurrentProjectile->InitProjectile(DamageType, ParticleEffect);
#if debug 
			UE_LOG(LogTemp, Display, TEXT("Spell casted"));
			//UE_LOG(LogTemp, Display, TEXT("Spell casted rotation %s"),*CameraRotator.ToString());
			//UE_LOG(LogTemp, Display, TEXT("Character rotation %s"),*MyCharacter->GetActorRotation().ToString());
#endif
		}
	}
}