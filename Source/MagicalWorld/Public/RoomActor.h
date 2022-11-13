// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.generated.h"


UENUM(BlueprintType)
enum class DoorLocation : uint8
{
	L UMETA(DisplayName = "L"),
	R UMETA(DisplayName = "R"),
	T UMETA(DisplayName = "T"),
	D UMETA(DisplayName = "D"),
	LR UMETA(DisplayName = "LR"),
	TD UMETA(DisplayName = "TD"),
	TR UMETA(DisplayName = "TR"),
	TL UMETA(DisplayName = "TL"),
	DR UMETA(DisplayName = "DR")
};

UCLASS()
class MAGICALWORLD_API ARoomActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnCubeEnemy();

	void SpawnSphereEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Where are the doors in this room 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	DoorLocation Doors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UInstancedStaticMeshComponent* Floor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UInstancedStaticMeshComponent* Wall;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FRandomStream RoomStream;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AActor> DoorActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AActor> EndPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AActor> EnemyToSpawnInTheRoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AActor> EnemyToSpawnInTheRoom2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AActor> PatrolPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AActor> AcquireAbilityActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AActor> GiveManaActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxEnemiesToSpawnInARoom = 2;

	int32 RoomFloorsX;

	int32 RoomFloorsY;

	int32 TileSizeX = 400;

	int32 TileSizeY = 400;

	bool WallOrDoor();

	void SpawnDoor(FVector Location, FRotator Rotation);

	void SpawnWall(UInstancedStaticMeshComponent* WallToAddInstance ,FVector Location, FRotator Rotation);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	bool Origin = false;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//class UInstancedStaticMeshComponent* Wall_R;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//class UInstancedStaticMeshComponent* Wall_T;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//class UInstancedStaticMeshComponent* Wall_D;
};
