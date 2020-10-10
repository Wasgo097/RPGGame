// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
AProjectile::AProjectile(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	// Use a sphere as a simple collision representation
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);// set up a notification for when this component hits something blocking
	// Players can't walk on it
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	// Set as root component
	RootComponent = CollisionComponent;
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComponent;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0;
	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}
// Called when the game starts or when spawned
void AProjectile::BeginPlay(){
	Super::BeginPlay();	
}
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics()){
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		if(DestroyParticle)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle,GetActorLocation());
		else 
			UE_LOG(LogTemp, Display, TEXT("Projectile hasn't destroyparticle %s"), *(GetFName().ToString()));
		Destroy();
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Projectile isn't valid during OnHit %s"), * (GetFName().ToString()));
	}
}
void AProjectile::InitProjectile(TSubclassOf<UDamageType> ProjectileDamageType){
	DamageType = ProjectileDamageType;
	bIsValid = DamageType != nullptr && DestroyParticle != nullptr && MovementParticle != nullptr;
}
// Called every frame
//void AProjectile::Tick(float DeltaTime){
//	Super::Tick(DeltaTime);
//}

