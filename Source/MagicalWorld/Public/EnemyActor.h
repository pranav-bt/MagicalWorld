// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class MAGICALWORLD_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UWidgetComponent* EnemyWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* HealthText;

	void DealDamage(int32 Damage);

	int32 Health = 100;
};
