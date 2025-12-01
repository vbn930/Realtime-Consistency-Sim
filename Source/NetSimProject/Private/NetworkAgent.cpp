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

    if (!bIsEnablePrediction) return;

    if (!bHasSynchronizedTime) return;

    float CurrentClientTime = GetWorld()->GetTimeSeconds();
    float EstimatedServerTime = CurrentClientTime + ClientServerTimeDelta;
    float RenderTime = EstimatedServerTime - InterpolationDelay;

    FVector NewLocation = GetActorLocation();
    FVector NewVelocity = FVector::ZeroVector;
    bool bFoundInterpolation = false;

    float MaxInterpGap = 0.5f;

    // Interpolation
    for (int32 i = 0; i < SnapshotBuffer.Num() - 1; i++)
    {
        const FEntitySnapshot& Start = SnapshotBuffer[i];
        const FEntitySnapshot& End = SnapshotBuffer[i + 1];

        if (Start.ServerTimestamp <= RenderTime && End.ServerTimestamp > RenderTime)
        {
            float TimeGap = End.ServerTimestamp - Start.ServerTimestamp;
            if (TimeGap > MaxInterpGap)
            {
                break;
            }

            float Alpha = 0.0f;
            if (TimeGap > KINDA_SMALL_NUMBER)
            {
                Alpha = (RenderTime - Start.ServerTimestamp) / TimeGap;
            }

            NewLocation = FMath::Lerp(Start.Position, End.Position, Alpha);
            NewVelocity = FMath::Lerp(Start.Velocity, End.Velocity, Alpha);

            bFoundInterpolation = true;
            bIsDeadReckoning = false;
            break;
        }
    }

    // Dead Reckoning
    if (!bFoundInterpolation && LastValidSnapshot.ServerTimestamp > 0.0f)
    {
        bIsDeadReckoning = true;

        float TimeSinceLast = RenderTime - LastValidSnapshot.ServerTimestamp;

        if (TimeSinceLast > 0)
        {
            FVector PredictedPos = LastValidSnapshot.Position + (LastValidSnapshot.Velocity * TimeSinceLast);
            NewLocation = FMath::VInterpTo(GetActorLocation(), PredictedPos, DeltaTime, 15.0f);
            NewVelocity = LastValidSnapshot.Velocity;
        }
    }

    SetActorLocation(NewLocation);
    GetCharacterMovement()->Velocity = NewVelocity;
}

// Called to bind functionality to input
void ANetworkAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int32 ANetworkAgent::GetCurrentAlgorithmState() const
{
    if (!bIsEnablePrediction) return 0; // OFF

    if (bIsDeadReckoning) return 2; // Dead Reckoning

    return 1; // Interpolation
}

void ANetworkAgent::UpdateTargetLocation(const FEntitySnapshot& Snapshot)
{
    if (!bHasSynchronizedTime)
    {
        float CurrentClientTime = GetWorld()->GetTimeSeconds();
        ClientServerTimeDelta = Snapshot.ServerTimestamp - CurrentClientTime;

        bHasSynchronizedTime = true;

        UE_LOG(LogTemp, Warning, TEXT("Time Synchronized! Delta: %f"), ClientServerTimeDelta);
    }

    if (bIsEnablePrediction)
    {
        SnapshotBuffer.Add(Snapshot);

        if (Snapshot.ServerTimestamp > LastValidSnapshot.ServerTimestamp)
        {
            LastValidSnapshot = Snapshot;
        }

        if (SnapshotBuffer.Num() > 50)
        {
            SnapshotBuffer.RemoveAt(0);
        }
    }
    else
    {
        SetActorLocation(Snapshot.Position);
        SnapshotBuffer.Empty();
    }
}