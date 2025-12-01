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

	// Save experiment data
    int32 AlgoState = GetCurrentAlgorithmState();
    AddExperimentDataToBuffer(CurrentClientTime, RealTimeServerSnapshot.Position, NewLocation,
		RealTimeServerSnapshot.ServerTimestamp, RealTimeServerSnapshot.Velocity, NewVelocity, AlgoState);
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

void ANetworkAgent::UpdateTargetOriginalLocation(const FEntitySnapshot& Snapshot)
{
	RealTimeServerSnapshot = Snapshot;
}

void ANetworkAgent::AddExperimentDataToBuffer(float CurrentTime, FVector ServerPos, FVector ClientPos, float ServerTime, FVector ServerVel, FVector ClientVel, int AlgoState)
{
    float PositionError = FVector::Dist(ServerPos, ClientPos);
    FString DataLine = FString::Printf(TEXT("%.3f,%.2f,%.2f,%.2f,%.2f,%.4f,%.3f,%.2f,%.2f,%.2f,%.2f,%d"),
        CurrentTime,
        ServerPos.X, ServerPos.Y,
        ClientPos.X, ClientPos.Y,
        PositionError,
        ServerTime,
        ServerVel.X, ServerVel.Y,
        ClientVel.X, ClientVel.Y,
        AlgoState
    );

    ExperimentDataBuffer.Add(DataLine);
}

void ANetworkAgent::SaveExperimentData()
{
    if (ExperimentDataBuffer.Num() == 0) return;

    // 1. CSV 헤더 만들기 (엑셀 맨 윗줄)
    FString FinalOutput = TEXT("Time,ServerX,ServerY,ClientX,ClientY,Error,ServerTime,ServerVelX,ServerVelY,ClientVelX,ClientVelY,State\n");

    // 2. 버퍼 내용을 하나의 긴 문자열로 합치기
    for (const FString& Line : ExperimentDataBuffer)
    {
        FinalOutput += Line + TEXT("\n"); // 줄바꿈 추가
    }

    // 3. 파일명 생성 (날짜_시간.csv) -> 덮어쓰기 방지
    FString FileName = FString::Printf(TEXT("Experiment_%s.csv"), *FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S")));

    // 4. 저장 경로: 프로젝트폴더/Saved/Logs/ 안에 저장
    FString FilePath = FPaths::ProjectSavedDir() + "Logs/" + FileName;

    // 5. 실제 쓰기 수행
    if (FFileHelper::SaveStringToFile(FinalOutput, *FilePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("=== Experiment Data Saved: %s ==="), *FilePath);
        UE_LOG(LogTemp, Warning, TEXT("Total Frames Recorded: %d"), ExperimentDataBuffer.Num());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to save file!"));
    }
}
