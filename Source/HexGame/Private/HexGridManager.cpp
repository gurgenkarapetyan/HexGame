// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridManager.h"

#include "Actors/HexTile.h"

AHexGridManager::AHexGridManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AHexGridManager::BeginPlay()
{
	Super::BeginPlay();

	if (!HexTile)
	{
		return;
	}

	// GenerateRandomGridSize();
	GenerateHexGrid2DArray();
}

void AHexGridManager::GenerateRandomGridSize()
{
	GridHeight = FMath::RandRange(0, 100);
	GridWidth = FMath::RandRange(0, 100);
}

void AHexGridManager::GenerateHexGrid2DArray()
{
	HexGrid2DArray.SetNumZeroed(GridWidth);
	for (int32 i = 0; i < HexGrid2DArray.Num(); ++i)
	{
		HexGrid2DArray[i].SetNumZeroed(GridHeight);
	}

	SetupHexTiles();
}

void AHexGridManager::SetupHexTiles()
{
	for (int32 y = 0; y < GridHeight; ++y)
	{
		for (int32 x = 0; x < GridWidth; ++x)
		{
			const bool bOddRow = y % 2 == 1;
			const float PositionX = bOddRow ? (x * TileHorizontalOffset) + OddRowHorizontalOffset : x * TileHorizontalOffset;
			const float PositionY = y * TileVerticalOffset;
			
			AHexTile* NewTile = GetWorld()->SpawnActor<AHexTile>(HexTile, FVector(FIntPoint(PositionX, PositionY)), FRotator::ZeroRotator);
			NewTile->SetTileIndex(FIntPoint(x, y));
			HexGrid2DArray[x][y] = NewTile;
		}
	}
}

FVector AHexGridManager::GetLocationFromIndex(const FIntPoint& Position) const noexcept
{
	return HexGrid2DArray[Position.X][Position.Y]->GetActorLocation();
}
