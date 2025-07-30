// Copyright Epic Games, Inc. All Rights Reserved.


#include "Core/GameModes/HexGameGameModeBase.h"
#include "HexGridManager.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Ball.h"


void AHexGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	InitHexGridManagerReference();
	SpawnBallPlayersOnGrid();
}

void AHexGameGameModeBase::InitHexGridManagerReference()
{
	TArray<AActor*> GridActors;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHexGridManager::StaticClass(), GridActors);
	if (GridActors.Num() == 0 || GridActors.Num() > 1)
	{
		return;
	}

	HexGridManager = Cast<AHexGridManager>(GridActors[0]);
}

void AHexGameGameModeBase::SpawnBallPlayersOnGrid() const noexcept
{
	for (const TSubclassOf<ABall>& Player:  BallPlayers)
	{
		SpawnBallOnGridRandomly(Player);
	}
}

void AHexGameGameModeBase::SpawnBallOnGridRandomly(const TSubclassOf<ABall>& Player) const noexcept
{
	if (!HexGridManager)
	{
		return;
	}
	
	const int32 PositionX = FMath::RandRange(0, HexGridManager->GetWidth() - 1);
	const int32 PositionY = FMath::RandRange(0, HexGridManager->GetHeight() - 1);
	const FIntPoint RandomPosition = FIntPoint(PositionX, PositionY);
	
	const FVector HexTileLocation = HexGridManager->GetLocationFromIndex(RandomPosition);
	ABall* SpawnedPlayer = GetWorld()->SpawnActor<ABall>(Player, FVector(HexTileLocation.X, HexTileLocation.Y, 60.f), FRotator());
	SpawnedPlayer->SetGridPosition(RandomPosition);
	SpawnedPlayer->SetGridManager(HexGridManager);
}
