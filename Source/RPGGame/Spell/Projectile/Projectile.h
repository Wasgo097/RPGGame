// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
UCLASS()
class RPGGAME_API AProjectile : public AActor{
	GENERATED_BODY()
protected:
	/** Sphere collision component */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Gameplay")
		class USphereComponent* CollisionComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
		class UStaticMeshComponent* StaticMesh;
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		class UProjectileMovementComponent* ProjectileMovement;
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
		class UParticleSystem* MovementParticle;*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
		UParticleSystem* DestroyParticle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
		TSubclassOf<class UDamageType> DamageType;
	float Damage = 0.0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Sets default values for this actor's properties
	AProjectile();
	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	void InitProjectile(TSubclassOf<UDamageType> InProjectileDamageType, UParticleSystem*InDestroyParticle,float InDamage);
	virtual bool ProjectileIsValid() { return bIsValid; }
private:
	bool bIsValid = false;
};