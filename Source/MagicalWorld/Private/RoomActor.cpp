// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomActor.h"
#include "../MagicalWorldCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
ARoomActor::ARoomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Floor = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Floor"));
	Wall = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Wall"));
	Floor->SetupAttachment(RootComponent);
	/*Wall_R = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Wall_R"));
	Wall_L = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Wall_L"));
	Wall_D = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Wall_D"));*/
}

// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
	Super::BeginPlay();
	
	RoomFloorsX = FMath::RandRange(5, 15);
	RoomFloorsY = FMath::RandRange(5, 15);

	for (int i = 0; i < RoomFloorsX - 1; i++)
	{
		for(int j = 0 ; j < RoomFloorsY - 1; j++)
		{ 
			FVector LocationToSpawn = FVector(i * TileSizeX, j * TileSizeY, 0);
			FTransform TransformToSpawn = FTransform(LocationToSpawn);
			Floor->AddInstance(TransformToSpawn);
		}
	}

	int32 TotalDoorCount = 0;
	int32 TopWallDoorCount = 0;
	int32 BottomWallDoorCount = 0;
	int32 RightWallDoorCount = 0;
	int32 LeftWallDoorCount = 0;

	//Bottom and Top walls
	for (int i = 0; i < RoomFloorsY - 1; i++)
	{
		bool Door = false;
		bool EntryCheck = (Origin || i != 0);
		//bool WallOrDoor = (i % 2) == 1;
		//if (BottomWallDoorCount < 1)
		//{
		//	int32 val = FMath::FRandRange(4, 10);
		//	Door = val % 5 == 0;
		//}

		FVector BottomWallLocation = FVector(GetActorLocation().X, TileSizeY * i + GetActorLocation().Y, 0);
		FRotator BottomWallRotation = FRotator(0, 90, 0);
		FTransform BottomWallTransform = FTransform(BottomWallRotation, BottomWallLocation);
		if (!Door && EntryCheck)
			Wall->AddInstance(BottomWallTransform);
		else if(EntryCheck)
		{ 
			SpawnDoor(BottomWallLocation, BottomWallRotation);
			BottomWallDoorCount++;
		}
			
		Door = false;
		AMagicalWorldCharacter* player = Cast<AMagicalWorldCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (TopWallDoorCount < 1 && player->CurrentDungeons < player->MaxDungeonsToCreate)
		{
			int32 val = FMath::FRandRange(4, 10);
			Door = val % 5 == 0;
			if (i == RoomFloorsY - 2 && TopWallDoorCount == 0 && player && player->CurrentDungeons < player->MaxDungeonsToCreate)
			{
				Door = true;
			}
		}

		double X = (RoomFloorsX-1) * TileSizeX;
		double Y = (i + 1) * TileSizeY;

		FVector TopWallLocation = FVector(GetActorLocation().X + X, GetActorLocation().Y + Y, 0);
		FRotator TopWallRotation = FRotator(0, -90, 0);
		FTransform TopWallTransform = FTransform(TopWallRotation, TopWallLocation);
		if(!Door)
			Wall->AddInstance(TopWallTransform);
		else
		{
			SpawnDoor(TopWallLocation, TopWallRotation);
			TopWallDoorCount++;
		}
	}

	// Right and Left walls
	for (int i = 0; i < RoomFloorsX - 1; i++)
	{
		bool Door = false;
		//bool WallOrDoor = (i % 2) == 1;
		//if (RightWallDoorCount < 1)
		//{
		//	int32 val = FMath::FRandRange(4, 10);
		//	Door = val % 5 == 0;
		//}

		FVector RightWallLocation = FVector(GetActorLocation().X + (TileSizeX * i), GetActorLocation().Y + TileSizeY * (RoomFloorsY - 1), 0);
		FRotator RightWallRotation = FRotator(0, 0, 0);
		FTransform RightWallTransform = FTransform(RightWallRotation, RightWallLocation);
		if(!Door)
			Wall->AddInstance(RightWallTransform);
		else
		{
			SpawnDoor(RightWallLocation, RightWallRotation);
			RightWallDoorCount++;
		}


		Door = false;
		FVector LeftWallLocation = FVector(GetActorLocation().X + TileSizeX * i, GetActorLocation().Y, 0);
		FRotator LeftWallRotation = FRotator(0, 0, 0);
		FTransform LeftWallTransform = FTransform(LeftWallRotation, LeftWallLocation);
		if(!Door)
			Wall->AddInstance(LeftWallTransform);
		else
		{
			SpawnDoor(LeftWallLocation, LeftWallRotation);
			LeftWallDoorCount++;
		}
		
	}

	AMagicalWorldCharacter* player = Cast<AMagicalWorldCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player->CurrentDungeons >= player->MaxDungeonsToCreate)
	{
		double x = FMath::RandRange(2, RoomFloorsX - 3) * TileSizeX;
		double y = FMath::RandRange(2, RoomFloorsY - 3) * TileSizeY;
		GetWorld()->SpawnActor<AActor>(EndPoint, FTransform(FRotator(0, 0, 0), GetActorLocation() + FVector(x, y, 5)));
	}
}

// Called every frame
void ARoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ARoomActor::WallOrDoor()
{
	//RoomStream.randomboolwithweight
	return false;
}

void ARoomActor::SpawnDoor(FVector Location, FRotator Rotation)
{
	//FVector Vect = GetActorTransform().TransformPosition(Location);
	//FRotator Rot = GetActorTransform().TransformRotation(Rotation.Quaternion()).Rotator();
	GetWorld()->SpawnActor<AActor>(DoorActor, FTransform(Rotation, Location));
	AMagicalWorldCharacter* player = Cast<AMagicalWorldCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->CurrentDungeons++;
}

void ARoomActor::SpawnWall(UInstancedStaticMeshComponent* WallToAddInstance, FVector Location, FRotator Rotation)
{
	//FVector Vect = GetActorTransform().TransformPosition(Location);
	//FRotator Rot = GetActorTransform().TransformRotation(Rotation.Quaternion()).Rotator();
	FTransform Transform = FTransform(Rotation, Location);
	WallToAddInstance->AddInstance(Transform);
}

