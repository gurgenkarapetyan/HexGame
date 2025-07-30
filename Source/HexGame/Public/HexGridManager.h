// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/HexTile.h"
#include "GameFramework/Actor.h"
#include "HexGridManager.generated.h"

class AHexTile;

UCLASS()
class HEXGAME_API AHexGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AHexGridManager();

	virtual void BeginPlay() override;

	FVector GetLocationFromIndex(const FIntPoint& Position) const noexcept;

	FORCEINLINE_DEBUGGABLE int32 GetWidth() const noexcept { return GridWidth; }
	FORCEINLINE_DEBUGGABLE int32 GetHeight() const noexcept { return GridHeight; }
	
private:
	void GenerateRandomGridSize();
	
	void GenerateHexGrid2DArray();
	void SetupHexTiles();
	
protected:
	TArray<TArray<AHexTile*>> HexGrid2DArray;
	
	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 GridWidth;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 GridHeight;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float TileHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float OddRowHorizontalOffset;
	
	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float TileVerticalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> HexTile;
};
