// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile.h"
#include "../../Character/RPGGameCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#define debug 1
// Sets default values
AProjectile::AProjectile(){
	//PrimaryActorTick.bCanEverTick = true;
	/*StaticMesh = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("MeshComp"));
	StaticMesh->AttachTo(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = StaticMesh;*/
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(20.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->SetupAttachment(RootComponent);
	RootComponent = CollisionComponent;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComponent;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0;
	InitialLifeSpan = 3.0f;
}
// Called when the game starts or when spawned
void AProjectile::BeginPlay(){
	Super::BeginPlay();
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	// Only add impulse and destroy projectile if we hit a physics
#if debug
	UE_LOG(LogTemp, Display, TEXT("OnHit"));
	DrawDebugSphere(GetWorld(), Hit.Location, 4.0, 12, FColor::Red, false, 10.0, 0, 1.0);
#endif
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics()) {
		if (ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)){
			UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, MyCharacter, DamageType);
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
			if (DestroyParticle)
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorLocation());
			else
				UE_LOG(LogTemp, Display, TEXT("Projectile hasn't destroyparticle %s"), *(GetFName().ToString()));
			Destroy();
		}
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Projectile isn't valid during OnHit %s"), * (GetFName().ToString()));
	}
}
void AProjectile::InitProjectile(TSubclassOf<UDamageType> InProjectileDamageType, UParticleSystem* InDestroyParticle, float InDamage){
	DamageType = InProjectileDamageType;
	DestroyParticle = InDestroyParticle;
	bIsValid = DamageType != nullptr && DestroyParticle != nullptr && MovementParticle != nullptr;
	Damage = InDamage;
}
// Called every frame
//void AProjectile::Tick(float DeltaTime){
//	Super::Tick(DeltaTime);
//}