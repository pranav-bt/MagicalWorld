// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MagicSpell.h"
#include "BaseEnemyCharacter.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MAGICALWORLD_API AEnemyCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* EnemyWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* HealthText;

	void DealDamage(int32 Damage);

	int32 Health = 100;

	class ACubeAIController* AIController;

	UPROPERTY(BlueprintReadWrite)
	float AttackRange = 500.0f;

	UPROPERTY(BlueprintReadWrite)
	float HealthToTeleport = 50.0f;

	void ChangeStateConditions();

	UPROPERTY(EditInstanceOnly)
	TArray<class AActor*> PatrolPoints;

	UPROPERTY(EditInstanceOnly)
	TArray<class AActor*> TeleportPoints;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AMagicSpell> EnemySpell;
};
