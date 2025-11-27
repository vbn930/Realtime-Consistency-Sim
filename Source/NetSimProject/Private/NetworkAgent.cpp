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

    // 예측 모드가 아니면 Tick 연산 안 함
    if (!bIsEnablePrediction) return;

    // -------------------------------------------------------
    // 1. 렌더링 시간(Render Time) 계산
    // -------------------------------------------------------
    // 현재 월드 시간보다 'InterpolationDelay'만큼 과거를 그립니다.
    float CurrentWorldTime = GetWorld()->GetTimeSeconds();
    float RenderTime = CurrentWorldTime - InterpolationDelay;

    // 계산될 최종 위치와 속도
    FVector NewLocation = GetActorLocation();
    FVector NewVelocity = FVector::ZeroVector;
    bool bFoundInterpolation = false;

    // -------------------------------------------------------
    // 2. Plan A: 보간 (Interpolation) 시도
    // -------------------------------------------------------
    // 버퍼에서 RenderTime을 사이에 둔 두 개의 스냅샷을 찾습니다.
    for (int32 i = 0; i < SnapshotBuffer.Num() - 1; i++)
    {
        const FEntitySnapshot& Start = SnapshotBuffer[i];
        const FEntitySnapshot& End = SnapshotBuffer[i + 1];

        // Start <= RenderTime < End 인 구간 발견!
        if (Start.ServerTimestamp <= RenderTime && End.ServerTimestamp > RenderTime)
        {
            // 보간 비율 (Alpha) 계산 (0.0 ~ 1.0)
            float TimeDiff = End.ServerTimestamp - Start.ServerTimestamp;
            float Alpha = 0.0f;
            if (TimeDiff > KINDA_SMALL_NUMBER)
            {
                Alpha = (RenderTime - Start.ServerTimestamp) / TimeDiff;
            }

            // 위치 보간 (Lerp)
            NewLocation = FMath::Lerp(Start.Position, End.Position, Alpha);

            // 속도 보간 (애니메이션용)
            NewVelocity = FMath::Lerp(Start.Velocity, End.Velocity, Alpha);

            bFoundInterpolation = true;
            bIsDeadReckoning = false;
            break; // 찾았으니 루프 종료
        }
    }

    // -------------------------------------------------------
    // 3. Plan B: 추측 항법 (Dead Reckoning) 시도
    // -------------------------------------------------------
    // 미래 데이터가 없어서 보간을 못 했다면 (패킷 로스 or 랙 발생)
    if (!bFoundInterpolation && SnapshotBuffer.Num() > 0)
    {
        bIsDeadReckoning = true;

        // 마지막으로 믿을 수 있는 데이터 (LastValidSnapshot) 사용
        // 그 시점으로부터 시간이 얼마나 흘렀는지 계산
        float TimeSinceLast = RenderTime - LastValidSnapshot.ServerTimestamp;

        if (TimeSinceLast > 0)
        {
            // ★ 추측 공식: P = P0 + V * t
            // 현재 위치 = 마지막위치 + (속도 * 흐른시간)
            FVector PredictedPos = LastValidSnapshot.Position + (LastValidSnapshot.Velocity * TimeSinceLast);

            // [Soft Correction]
            // 추측 위치로 바로 텔레포트하면 튈 수 있으므로, 현재 위치에서 부드럽게 이동
            // VInterpTo를 사용하여 급격한 변화를 스무딩
            NewLocation = FMath::VInterpTo(GetActorLocation(), PredictedPos, DeltaTime, 15.0f);

            // 속도는 마지막 속도 유지 (관성)
            NewVelocity = LastValidSnapshot.Velocity;
        }
    }

    // -------------------------------------------------------
    // 4. 최종 적용
    // -------------------------------------------------------
    SetActorLocation(NewLocation);

    // 애니메이션 시스템이 Velocity를 인식하도록 설정
    GetCharacterMovement()->Velocity = NewVelocity;

    // [디버깅] DR 상태일 때 머리 위에 빨간 점 표시
    if (bIsDeadReckoning)
    {
        DrawDebugPoint(GetWorld(), GetActorLocation() + FVector(0, 0, 100), 10.0f, FColor::Red, false, 0.03f);
    }
}

// Called to bind functionality to input
void ANetworkAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANetworkAgent::UpdateTargetLocation(const FEntitySnapshot& Snapshot)
{
    if (bIsEnablePrediction)
    {
        // 1. 버퍼에 저장 (시간순 정렬되었다고 가정)
        SnapshotBuffer.Add(Snapshot);

        // 2. 가장 최신 데이터 갱신 (추측 항법의 기준점)
        // 타임스탬프가 더 최신인 경우에만 갱신
        if (Snapshot.ServerTimestamp > LastValidSnapshot.ServerTimestamp)
        {
            LastValidSnapshot = Snapshot;
        }

        // 3. 버퍼 관리: 너무 오래된(2초 지난) 데이터는 삭제하여 메모리 절약
        if (SnapshotBuffer.Num() > 0)
        {
            // 가장 최신 데이터 시간 기준으로 2초 지난 건 삭제
            float TimeThreshold = SnapshotBuffer.Last().ServerTimestamp - 2.0f;
            while (SnapshotBuffer.Num() > 0 && SnapshotBuffer[0].ServerTimestamp < TimeThreshold)
            {
                SnapshotBuffer.RemoveAt(0);
            }
        }
    }
    // [OFF] 예측 끄면 그냥 텔레포트
    else
    {
        SetActorLocation(Snapshot.Position);
        SnapshotBuffer.Empty(); // 버퍼 비우기
    }
}



