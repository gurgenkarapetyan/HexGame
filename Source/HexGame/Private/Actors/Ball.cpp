// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Ball.h"
#include "HexGridManager.h"
#include "Components/BallMovementComponent.h"
#include "Components/HealthComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = SphereCollision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereCollision);

	AttackParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Attack Particle"));
	AttackParticleSystem->SetupAttachment(SphereCollision);

	BallMovementComponent = CreateDefaultSubobject<UBallMovementComponent>(TEXT("Ball Movement Component"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void ABall::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh)
	{
		DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);
	}
}

void ABall::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!GridManager)
	{
		return;
	}

	const FVector LocationOnGrid = GridManager->GetLocationFromIndex(CurrentPosition);
	const FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), FVector(LocationOnGrid.X, LocationOnGrid.Y, 60.f), DeltaSeconds, 1000.f);
	SetActorLocation(NewLocation);
}

void ABall::Fire(AActor* Enemy)
{
	if (!Enemy || !AttackParticleSystem)
	{
		return;
	}

	DynamicMaterial->SetScalarParameterValue("Brightness", 20.0f);
	AttackParticleSystem->Activate();
	AttackParticleSystem->SetBeamTargetPoint(0 , Enemy->GetActorLocation(), 0);
	const float RandomDamageAmount = FMath::RandRange(2.f, 5.f);
	UGameplayStatics::ApplyDamage(Enemy, RandomDamageAmount, nullptr, this, UDamageType::StaticClass());
}
