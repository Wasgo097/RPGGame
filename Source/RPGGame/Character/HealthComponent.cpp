// Fill out your copyright notice in the Description page of Project Settings.
#include "HealthComponent.h"
#include "../Utilities//MyDamageTypes.h"
#include "GameFramework/DamageType.h"
// Sets default values for this component's properties
UHealthComponent::UHealthComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UHealthComponent::BeginPlay(){
	Super::BeginPlay();
	ActualHealth = MaxHealth*0.5;
	//ActualHealth = MaxHealth;
	AActor* Owner = GetOwner();
	if (Owner)
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
}
void UHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser){
	if (DamageType->GetClass() == URestoreHealth::StaticClass())
		Damage *= -1.0;
	ActualHealth = FMath::Clamp(ActualHealth - Damage, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Display, TEXT("Actual HP = %f"), ActualHealth);
}
float UHealthComponent::GetRatio() {
	return ActualHealth / MaxHealth;
}
// Called every frame
//void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}

