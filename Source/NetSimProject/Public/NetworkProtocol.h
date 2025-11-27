// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// byte alignment
#pragma pack(push, 1)

enum class EPacketType : uint8 {
    DUMMY = 0,
	SNAPSHOT,
	INPUT,
};

struct FPacketHeader
{
	EPacketType Type;
	int32 Size;
};

struct FEntitySnapshot
{
    FPacketHeader Header;
    FVector Position;
    FVector Velocity;
    float ServerTimestamp;

    FEntitySnapshot()
    {
        Header.Type = EPacketType::SNAPSHOT;
        Header.Size = sizeof(FEntitySnapshot);
    }
};

#pragma pack(pop)