// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Actors/Ball.h"
#include "Particles/ParticleSystemComponent.h"

UHealthComponent::UHealthComponent()
	: Health(10.f)
{
	
	PrimaryComponentTick.bCanEverTick = false;

	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f)
	{
		return;
	}
	
	Health -= Damage;
	
	if (Health <= 0)
	{
		DamagedActor->Destroy();

		if (const ABall* const DamageCauserBall = Cast<ABall>(DamageCauser))
		{
			DamageCauserBall->GetAttackParticleSystemComponent()->Deactivate();
		}
	}
}



