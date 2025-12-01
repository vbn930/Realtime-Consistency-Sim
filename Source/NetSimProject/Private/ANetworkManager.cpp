#include "ANetworkManager.h"

// Sets default values
AANetworkManager::AANetworkManager()
{ 
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AANetworkManager::BeginPlay()
{
	Super::BeginPlay();

	//Mocking dedicated server
	FString Mode;
	UWorld* World = GetWorld();

	ENetMode CurrentNetMode = World->GetNetMode();
	UE_LOG(LogTemp, Warning, TEXT("[NetworkManager] BeginPlay - NetMode: %d"), (int32)CurrentNetMode);
	bool isServer = (FParse::Value(FCommandLine::Get(), TEXT("mode="), Mode) && Mode == "server");
}

void AANetworkManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (Socket) {
		Socket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
		Socket = nullptr;
	}
}

// Called every frame
void AANetworkManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Socket) {
		if (bIsServer) {
			ProcessIncomingPackets();
			RunServerSimulation(DeltaTime);
		}
		else {
			ProcessIncomingPackets();
			DispatchDelayedPackets();
		}
	}

}

bool AANetworkManager::StartServer(int32 Port)
{
	Socket = FUdpSocketBuilder(TEXT("UDPServer"))
		.AsNonBlocking()
		.BoundToPort(Port)
		.Build();

	if (Socket) {
		UE_LOG(LogTemp, Warning, TEXT("Server Started on Port %d"), Port);
	}
	return (Socket != nullptr);
}

bool AANetworkManager::ConnectClient(const FString& Adderss, int32 Port)
{
	Socket = FUdpSocketBuilder(TEXT("UDPClient"))
		.AsNonBlocking()
		.BoundToPort(0)
		.Build();

	RemoteAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	// Save server addr
	bool bIsValid;
	RemoteAddr->SetIp(*Adderss, bIsValid);
	RemoteAddr->SetPort(Port);

	if (Socket) {
		UE_LOG(LogTemp, Warning, TEXT("Client Socket Created"));
	}

	return (Socket != nullptr);
}

void AANetworkManager::BroadcastSnapshot(const FEntitySnapshot& Snapshot)
{
	if (!Socket) {
		return;
	}

	int32 BytesSent = 0;

	for (TSharedPtr<FInternetAddr> ConnectedClientAddr : ConnectedClients) {
		Socket->SendTo(
			reinterpret_cast<const uint8*>(&Snapshot),
			sizeof(FEntitySnapshot),
			BytesSent,
			*ConnectedClientAddr
		);
	}
}

void AANetworkManager::SendPacketToServer(const FEntitySnapshot& Packet)
{
	if (!Socket || !RemoteAddr->IsValid()) {
		return;
	}

	int32 BytesSent = 0;

	Socket->SendTo(
		reinterpret_cast<const uint8*>(&Packet),
		sizeof(FEntitySnapshot),
		BytesSent,
		*RemoteAddr
	);
}

void AANetworkManager::ProcessIncomingPackets()
{
	uint32 Size;

	while (Socket->HasPendingData(Size)) {
		int32 BytesRead = 0;
		TSharedRef<FInternetAddr> SenderAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

		if (Socket->RecvFrom(ReceiveBuffer, sizeof(ReceiveBuffer), BytesRead, *SenderAddr)) {
			FEntitySnapshot* Snapshot = reinterpret_cast<FEntitySnapshot*>(ReceiveBuffer);

			if (Snapshot->Header.Type == EPacketType::DUMMY) {
				UE_LOG(LogTemp, Warning, TEXT("[Recv] Dummy Packet"));

				if (bIsServer) {
					if (!IsKnownClient(SenderAddr)) {
						ConnectedClients.Add(SenderAddr);
						UE_LOG(LogTemp, Warning, TEXT("New Client Registered: %s"), *SenderAddr->ToString(true));
					}
				}
				// Skip dummy packet
				return;
			}
			else if (Snapshot->Header.Type == EPacketType::SNAPSHOT) {
				// Send original packet for logging
				Agent->UpdateTargetOriginalLocation(*Snapshot);

				if (FMath::FRand() < SimulatedPacketLoss)
				{
					// Simulate Packet loss
					UE_LOG(LogTemp, Warning, TEXT("Packet Lost Simulated!"));
					continue;
				}

				FDelayedPacket DelayedPacket;
				DelayedPacket.Snapshot = *Snapshot;

				// Add jitter for simulate real time stuttering
				float Jitter = SimulatedLatency * FMath::RandRange(-0.2f, 0.2f);
				DelayedPacket.ProcessTime = GetWorld()->GetTimeSeconds() + SimulatedLatency + Jitter;

				IncomingPacketQueue.Add(DelayedPacket);
			}
		}
	}
}

void AANetworkManager::DispatchDelayedPackets()
{
	if (IncomingPacketQueue.Num() == 0) {
		return;
	}

	float CurrentTime = GetWorld()->GetTimeSeconds();
	
	while (IncomingPacketQueue.Num() > 0) {
		if (CurrentTime >= IncomingPacketQueue[0].ProcessTime) {
			FEntitySnapshot DataToApply = IncomingPacketQueue[0].Snapshot;

			if (Agent)
			{
				Agent->UpdateTargetLocation(DataToApply);
			}

			IncomingPacketQueue.RemoveAt(0);
		}
		else {
			break;
		}
	}
}

void AANetworkManager::SetAsServer()
{
	UE_LOG(LogTemp, Warning, TEXT("=== RUNNING AS DEDICATED SERVER ==="));
	StartServer(5000);
	bIsServer = true;
}

void AANetworkManager::SetAsClient()
{
	UE_LOG(LogTemp, Warning, TEXT("=== RUNNING AS CLIENT ==="));
	ConnectClient("127.0.0.1", 5000); // connect local host
	bIsServer = false;

	// Send dummy packet for registering client addr in the server
	FEntitySnapshot DummyPacket;
	DummyPacket.Header.Type = EPacketType::DUMMY;

	int32 BytesSent = 0;

	Socket->SendTo(reinterpret_cast<uint8*>(&DummyPacket), sizeof(DummyPacket), BytesSent, *RemoteAddr);
}

bool AANetworkManager::IsSocketEnabled()
{
	if (Socket) {
		return true;
	}
	return false;
}

FEntitySnapshot AANetworkManager::PacketFactory(EPacketType PacketType, FVector Postion, FVector Velocity, float ServerTimestamp)
{
	FEntitySnapshot Packet;
	
	Packet.Header.Type = PacketType;
	Packet.Position = Postion;
	Packet.Velocity = Velocity;
	Packet.ServerTimestamp = ServerTimestamp;

	return Packet;
}

bool AANetworkManager::IsKnownClient(TSharedPtr<FInternetAddr> Addr)
{
	FString IncomingIP = Addr->ToString(true);

	for (const auto& KnownAddr : ConnectedClients)
	{
		if (KnownAddr->ToString(true) == IncomingIP)
		{
			return true;
		}
	}

	return false;
}

void AANetworkManager::RunServerSimulation(float DeltaTime)
{
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSystem && Agent)
	{
		FVector CurrentPos = Agent->GetActorLocation();

		if (CurrentPathPoints.Num() == 0 || PathPointIndex >= CurrentPathPoints.Num()) {

			float Radius = PathfindingRadius;
			bool isFoundPath = false;
			while (!isFoundPath) {
				FNavLocation RandomLocation = GetVaildRandomLocation(CurrentPos, Radius);
				CalculateNavPath(CurrentPos, RandomLocation);

				if (CurrentPathPoints.Num()) {
					isFoundPath = true;
				}
			}
		}

		FVector TargetPoint = CurrentPathPoints[PathPointIndex];
		FVector Direction = (TargetPoint - CurrentPos).GetSafeNormal();
		float Speed = 600.0f;
		FVector CurrentVelocity = Direction * Speed;
		FVector NewPos = CurrentPos + (CurrentVelocity * DeltaTime);

		FNavLocation ProjectedLocation;

		if (NavSystem->ProjectPointToNavigation(NewPos, ProjectedLocation, FVector(500.0f, 500.0f, 500.0f)))
		{
			NewPos.Z = ProjectedLocation.Location.Z;
		}

		if (FVector::Dist(CurrentPos, TargetPoint) < 100.0f)
		{
			PathPointIndex++;
		}

		Agent->SetActorLocation(NewPos);

		FEntitySnapshot SnapShot = PacketFactory(EPacketType::SNAPSHOT, NewPos, CurrentVelocity, GetWorld()->GetTimeSeconds());
		BroadcastSnapshot(SnapShot);
	}
}

void AANetworkManager::CalculateNavPath(FVector StartPos, FVector EndPos)
{
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSystem)
	{
		UNavigationPath* Path = NavSystem->FindPathToLocationSynchronously(
			GetWorld(),
			StartPos,
			EndPos
		);

		if (Path && Path->IsValid())
		{
			CurrentPathPoints = Path->PathPoints;

			PathPointIndex = 1;

			UE_LOG(LogTemp, Log, TEXT("Path Found! Points: %d"), CurrentPathPoints.Num());
		}
		else {
			CurrentPathPoints.Reset();
			UE_LOG(LogTemp, Log, TEXT("Path Not Found! Restarted"));
		}
	}
}

FNavLocation AANetworkManager::GetVaildRandomLocation(FVector Origin, float Radius)
{
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation RandomResult;

	if (NavSystem) {
		if (NavSystem->GetRandomPointInNavigableRadius(Origin, Radius, RandomResult))
		{
			UE_LOG(LogTemp, Log, TEXT("New Random Target Found: %s"), *RandomResult.Location.ToString());
		}
	}

	return RandomResult;
}

