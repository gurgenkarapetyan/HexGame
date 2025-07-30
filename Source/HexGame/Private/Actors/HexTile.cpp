// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/HexTile.h"

AHexTile::AHexTile()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh"));
	TileMesh->SetupAttachment(RootComponent);
}
