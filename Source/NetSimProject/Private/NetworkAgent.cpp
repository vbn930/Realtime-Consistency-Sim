// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkAgent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ANetworkAgent::ANetworkAgent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	AutoPossessAI = EAutoPossessAI::Disabled;

    bReplicates = false;
    SetReplicateMovement(false);
    GetCharacterMovement()->SetIsReplicated(false);
    GetCharacterMovement()->GravityScale = 0.0f;
}

// Called when the game starts or when spawned
void ANetworkAgent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetworkAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bIsEnablePrediction)
    {
        FVector CurrentPos = GetActorLocation();

        FVector SmoothPos = FMath::VInterpTo(CurrentPos, TargetLocation, DeltaTime, 10.0f);
        SetActorLocation(SmoothPos);
    }
}

// Called to bind functionality to input
void ANetworkAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANetworkAgent::UpdateTargetLocation(const FEntitySnapshot& Snapshot)
{
    TargetLocation = Snapshot.Position;

    if (bIsEnablePrediction) {
        SnapshotBuffer.Add(Snapshot);

        if (Snapshot.ServerTimestamp > LastValidSnapshot.ServerTimestamp)
        {
            LastValidSnapshot = Snapshot;
        }

        if (SnapshotBuffer.Num() > 20) {
            SnapshotBuffer.RemoveAt(0);
        }
    }
    else {
        SetActorLocation(Snapshot.Position);
    }
}



