// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HexGameGameModeBase.generated.h"

class ABall;
class AHexGridManager;

UCLASS()
class HEXGAME_API AHexGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	void InitHexGridManagerReference();

	void SpawnBallPlayersOnGrid() const noexcept;
	void SpawnBallOnGridRandomly(const TSubclassOf<ABall>& BallPlayer) const noexcept;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Players")
	TArray<TSubclassOf<ABall>> BallPlayers;

private:
	AHexGridManager* HexGridManager;
};
