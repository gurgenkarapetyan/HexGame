// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UHealthComponent;
class UBallMovementComponent;
class USphereComponent;
class AHexGridManager;

UCLASS()
class HEXGAME_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	ABall();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	void Fire(AActor* Enemy);
	
	FORCEINLINE_DEBUGGABLE void SetGridPosition(const FIntPoint& NewPosition) noexcept { CurrentPosition = NewPosition; }
	FORCEINLINE_DEBUGGABLE FIntPoint GetGridPosition() const noexcept { return CurrentPosition; }

	FORCEINLINE_DEBUGGABLE void SetGridManager(AHexGridManager* HexGridManager) noexcept { GridManager = HexGridManager; }

	FORCEINLINE_DEBUGGABLE UParticleSystemComponent* GetAttackParticleSystemComponent() const noexcept { return AttackParticleSystem; }
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* DynamicMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Particle Effects", meta=(AllowPrivateAccess = "true"))
	UParticleSystemComponent* AttackParticleSystem;

	UPROPERTY(VisibleAnywhere)
	UBallMovementComponent* BallMovementComponent;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;
	
	UPROPERTY()
	AHexGridManager* GridManager;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Grid Position")
	FIntPoint CurrentPosition;
};
