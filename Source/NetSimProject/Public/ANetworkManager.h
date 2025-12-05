// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "NetworkProtocol.h"
#include "NetworkAgent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "ANetworkManager.generated.h"

UCLASS()
class NETSIMPROJECT_API AANetworkManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AANetworkManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool StartServer(int32 Port);
	bool ConnectClient(const FString& Adderss, int32 Port);

	// Server -> Clients
	void BroadcastSnapshot(const FEntitySnapshot& Snapshot);

	// Client -> Server
	void SendPacketToServer(const FEntitySnapshot& Packet);

	// Only client 
	void ProcessIncomingPackets();
	void DispatchDelayedPackets();

	UFUNCTION(BlueprintCallable, Category = "Network Simulation")
	void SetAsServer();

	UFUNCTION(BlueprintCallable, Category = "Network Simulation")
	void SetAsClient();

	UFUNCTION(BlueprintCallable, Category = "Network Simulation")
	bool IsSocketEnabled();

	UFUNCTION(BlueprintCallable, Category = "Simulation Control")
	void ForceUnstuckAgent();

private:
	FSocket* Socket;
	uint8 ReceiveBuffer[1024];

	struct FDelayedPacket
	{
		FEntitySnapshot Snapshot;
		double ProcessTime;
	};

	TArray<FDelayedPacket> IncomingPacketQueue;

	FEntitySnapshot PacketFactory(EPacketType PacketType, FVector Postion, FVector Velocity, float ServerTimestamp);

public:
	UPROPERTY(EditInstanceOnly, Category = "Experiment")
	ANetworkAgent* Agent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Simulation")
	float SimulatedLatency = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Simulation")
	float SimulatedPacketLoss = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Simulation")
	float PathfindingRadius = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Simulation")
	bool bIsServer = false;

private: // Managing clients

	// Save clients
	TArray<TSharedPtr<FInternetAddr>> ConnectedClients;
	bool IsKnownClient(TSharedPtr<FInternetAddr> Addr);

	// Server addr for client
	TSharedPtr<FInternetAddr> RemoteAddr = nullptr;

	void RunServerSimulation(float DeltaTime);

private: // Pathfinding
	TArray<FVector> CurrentPathPoints;

	int32 PathPointIndex = 0;

	int32 PathFindFailCount = 0;

	void CalculateNavPath(FVector StartPos, FVector EndPos);
	FNavLocation GetVaildRandomLocation(FVector Origin, float Radius);
};
