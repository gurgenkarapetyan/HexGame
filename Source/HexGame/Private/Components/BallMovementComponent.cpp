// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BallMovementComponent.h"
#include "Actors/Ball.h"
#include "Kismet/GameplayStatics.h"

UBallMovementComponent::UBallMovementComponent()
	: MovementRate(1.0f)
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UBallMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerBall = Cast<ABall>(GetOwner());
	if (OwnerBall)
	{
		GetWorld()->GetTimerManager().SetTimer(SimulateMovementTimerHandle, this, &UBallMovementComponent::StartMoving, MovementRate, true);
	}
}

void UBallMovementComponent::StartMoving()
{
	ABall* ClosestEnemyBall = FindClosestEnemyBall();
	if (!ClosestEnemyBall)
	{
		return;
	}

	const FIntPoint OwnerBallPosition = OwnerBall->GetGridPosition();
	const FIntPoint EnemyBallPosition = ClosestEnemyBall->GetGridPosition();

	const TPair<bool, FIntPoint> NextMovePosition = GetNextPosition(OwnerBallPosition, EnemyBallPosition);
	if (NextMovePosition.Key)
	{
		OwnerBall->SetGridPosition(NextMovePosition.Value);
	}
	else
	{
		OwnerBall->Fire(ClosestEnemyBall);
	}
}

ABall* UBallMovementComponent::FindClosestEnemyBall() const
{
	TArray<AActor*> FoundBalls;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), FoundBalls);

	for (AActor* FoundBall : FoundBalls)
	{
		if (OwnerBall != FoundBall)
		{
			return Cast<ABall>(FoundBall);
		}
	}
	
	return nullptr;
}

TPair<bool, FIntPoint> UBallMovementComponent::GetNextPosition(const FIntPoint& OwnerPosition, const FIntPoint& EnemyPosition)
{
	const int32 XCoordinateDistance = FMath::Clamp(EnemyPosition.X - OwnerPosition.X, -1, 1);
	FIntPoint CalculatedPosition;
	
	if (XCoordinateDistance == 1)
	{
		CalculatedPosition = OwnerPosition + FIntPoint(1, 0); 
	}
	else if (XCoordinateDistance == -1)
	{
		CalculatedPosition = OwnerPosition + FIntPoint(-1, 0); 
	}
	else if (XCoordinateDistance == 0)
	{
		const int32 YCoordinateDistance = FMath::Clamp(EnemyPosition.Y - OwnerPosition.Y, -1, 1);
		if (YCoordinateDistance == 1)
		{
			CalculatedPosition = OwnerPosition + FIntPoint(0, 1); 
		}
		else if (YCoordinateDistance == -1)
		{
			CalculatedPosition = OwnerPosition + FIntPoint(0, -1); 
		}
	}
	
	bool bCanStepOnGrid = CalculatedPosition != EnemyPosition;
	return TPair<bool, FIntPoint>(bCanStepOnGrid, CalculatedPosition);
}
