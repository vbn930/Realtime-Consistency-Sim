// Fill out your copyright notice in the Description page of Project Settings.


#include "SimPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

void ASimPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    TArray<AActor*> FoundCameras;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);

    for (AActor* Camera : FoundCameras)
    {
        if (Camera->ActorHasTag(TEXT("OverviewCamera")))
        {
            SetViewTargetWithBlend(Camera, 0.0f);

            UE_LOG(LogTemp, Warning, TEXT("Camera Switched to Overview!"));
            break;
        }
    }
}
