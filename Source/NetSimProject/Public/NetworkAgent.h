// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NetworkProtocol.h"
#include "NetworkAgent.generated.h"

UCLASS()
class NETSIMPROJECT_API ANetworkAgent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANetworkAgent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Simulation")
	bool bIsEnablePrediction = false;

	void UpdateTargetLocation(const FEntitySnapshot& Snapshot);

private:
	FVector TargetLocation;
	FVector TargetVelocity;
	FVector SimulatedVelocity;

	FEntitySnapshot LastValidSnapshot;
	TArray<FEntitySnapshot> SnapshotBuffer;
};
