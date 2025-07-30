// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexTile.generated.h"

UCLASS()
class HEXGAME_API AHexTile : public AActor
{
	GENERATED_BODY()
	
public:	
	AHexTile();

	FORCEINLINE_DEBUGGABLE FIntPoint GetTileIndex() const noexcept { return TileIndex; }
	FORCEINLINE_DEBUGGABLE void SetTileIndex(const FIntPoint& Index) noexcept { TileIndex = Index; }
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	UStaticMeshComponent*  TileMesh;

	UPROPERTY(VisibleInstanceOnly, Category = "Tile")
	FIntPoint TileIndex;
};
