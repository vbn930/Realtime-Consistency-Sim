// Fill out your copyright notice in the Description page of Project Settings.
#include "NetworkAgent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ANetworkManager.h"

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

void ANetworkAgent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

// Called every frame
void ANetworkAgent::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    bool bShouldMove = false;

    if (bIsEnablePrediction && bHasSynchronizedTime)
    {
        if (SnapshotBuffer.Num() > 0)
        {
            bShouldMove = true;
        }
    }

    if (bShouldMove)
    {
        float CurrentClientTime = GetWorld()->GetTimeSeconds();
        float EstimatedServerTime = CurrentClientTime + ClientServerTimeDelta;
        float RenderTime = EstimatedServerTime - InterpolationDelay;

        if (SnapshotBuffer[0].ServerTimestamp > RenderTime)
        {
            FVector StartPos = SnapshotBuffer[0].Position;
            FVector SmoothPos = FMath::VInterpTo(GetActorLocation(), StartPos, DeltaTime, 10.0f);
            SetActorLocation(SmoothPos);

            bShouldMove = false;
        }
        else
        {
            FVector NewLocation = GetActorLocation();
            FVector NewVelocity = FVector::ZeroVector;
            bool bFoundInterpolation = false;
            float MaxInterpGap = 0.5f;

            FEntitySnapshot DRSnapshot = LastValidSnapshot;

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
                        DRSnapshot = Start;
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
            if (!bFoundInterpolation && DRSnapshot.ServerTimestamp > 0.0f)
            {
                bIsDeadReckoning = true;
                float TimeSinceLast = RenderTime - DRSnapshot.ServerTimestamp;

                if (TimeSinceLast > 0)
                {
                    FVector PredictedPos = DRSnapshot.Position + (DRSnapshot.Velocity * TimeSinceLast);

                    NewLocation = FMath::VInterpTo(GetActorLocation(), PredictedPos, DeltaTime, 15.0f);
                    NewVelocity = DRSnapshot.Velocity;
                }
            }

            SetActorLocation(NewLocation);
            GetCharacterMovement()->Velocity = NewVelocity;
        }
    }

	// Data saving for Experiment
    if (bIsRecording)
    {
        float CurrentClientTime = GetWorld()->GetTimeSeconds();
        FVector CurrentPos = GetActorLocation();
        FVector CurrentVel = GetCharacterMovement()->Velocity;

        int32 AlgoState = GetCurrentAlgorithmState();

        AddExperimentDataToBuffer(
            CurrentClientTime,
            RealTimeServerSnapshot.Position,
            CurrentPos,
            RealTimeServerSnapshot.ServerTimestamp,
            RealTimeServerSnapshot.Velocity,
            CurrentVel,
            AlgoState
        );

        CurrentRecordingTime = GetWorld()->GetTimeSeconds() - RecordingStartTime;
    }
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

void ANetworkAgent::StartExperimentRecording()
{
    if (bIsRecording) return;

    ExperimentDataBuffer.Empty();
    bIsRecording = true;

    RecordingStartTime = GetWorld()->GetTimeSeconds();
    CurrentRecordingTime = 0.0f;

    UE_LOG(LogTemp, Warning, TEXT("=== Experiment Recording STARTED ==="));
}

void ANetworkAgent::StopExperimentRecording()
{
    if (!bIsRecording) return;

    bIsRecording = false;
    SaveExperimentData();

    UE_LOG(LogTemp, Warning, TEXT("=== Experiment Recording STOPPED & SAVED ==="));
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

    // 1. NetworkManager 찾아서 설정값 가져오기
    float CurrentLatency = 0.0f;
    float CurrentLoss = 0.0f;

    // 월드에 있는 NetworkManager를 찾습니다.
    AANetworkManager* NetMgr = Cast<AANetworkManager>(
        UGameplayStatics::GetActorOfClass(GetWorld(), AANetworkManager::StaticClass())
    );

    if (NetMgr)
    {
        CurrentLatency = NetMgr->SimulatedLatency * 1000.0f;
        CurrentLoss = NetMgr->SimulatedPacketLoss * 100.0f;
    }

    FString PredStatus = bIsEnablePrediction ? TEXT("ON") : TEXT("OFF");

    FString TimeStr = FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S"));

    FString FileName = FString::Printf(TEXT("Exp_Lat%.0f_Loss%.0f_%s_%s.csv"),
        CurrentLatency,
        CurrentLoss,
        *PredStatus,
        *TimeStr
    );

    FString FinalOutput = TEXT("Time,ServerX,ServerY,ClientX,ClientY,Error,ServerTime,ServerVelX,ServerVelY,ClientVelX,ClientVelY,State\n");

    for (const FString& Line : ExperimentDataBuffer)
    {
        FinalOutput += Line + TEXT("\n"); 
    }

    FString FilePath = FPaths::ProjectSavedDir() + "Logs/" + FileName;

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
