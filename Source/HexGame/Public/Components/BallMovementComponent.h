// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BallMovementComponent.generated.h"

class ABall;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEXGAME_API UBallMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBallMovementComponent();

	virtual void BeginPlay() override;

	void StartMoving();

private:
	ABall* FindClosestEnemyBall() const;
	
	TPair<bool, FIntPoint> GetNextPosition(const FIntPoint& OwnerPosition, const FIntPoint& EnemyPosition);
	
private:
	ABall* OwnerBall;
	
	FTimerHandle SimulateMovementTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Rate", meta = (AllowPrivateAccess="true"))
	float MovementRate;
};
