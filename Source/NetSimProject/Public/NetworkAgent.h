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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UFUNCTION(BlueprintPure, Category = "Network Status")
	int32 GetCurrentAlgorithmState() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Simulation")
	bool bIsEnablePrediction = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Experiment")
	bool bIsRecording = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Experiment")
	float CurrentRecordingTime = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Experiment")
	void StartExperimentRecording();

	UFUNCTION(BlueprintCallable, Category = "Experiment")
	void StopExperimentRecording();

	void UpdateTargetLocation(const FEntitySnapshot& Snapshot);
	void UpdateTargetOriginalLocation(const FEntitySnapshot& Snapshot);

	void AddExperimentDataToBuffer(float CurrentTime, FVector ServerPos, FVector ClientPos,
		float ServerTime, FVector ServerVel, FVector ClientVel, int AlgoState);
	void SaveExperimentData();

	float InterpolationDelay = 0.7f;

private:
	FVector TargetLocation;
	FVector TargetVelocity;
	FVector SimulatedVelocity;

	float ClientServerTimeDelta = 0.0f;
	bool bHasSynchronizedTime = false;

	bool bIsDeadReckoning = false;

	float RecordingStartTime = 0.0f;

	FEntitySnapshot RealTimeServerSnapshot;

	FEntitySnapshot LastValidSnapshot;
	TArray<FEntitySnapshot> SnapshotBuffer;
	TArray<FString> ExperimentDataBuffer;
};
