// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicAIController.h"
#include "CubeAIController.generated.h"

/**
 * 
 */
UCLASS()
class MAGICALWORLD_API ACubeAIController : public AMagicAIController
{
	GENERATED_BODY()
	
public:
	class AEnemyCharacter* CubeCharacter;

	enum CubeState
	{
		Idle,
		Patrol,
		Teleport,
		Attack
	};

	CubeState CurrentState;
	CubeState PreviousState;
	CubeState NextState;

	void ChangeState();

	void UpdateState();

	//State Functions
	void BeginPatrol();
	void MoveToNextPoint();
	void BeginTeleport();
	void BeginAttack();

	void ShootSpell();

	void UpdatePatrol();
	void UpdateTeleport();
	void UpdateAttack();

	void EndPatrol();
	void EndTeleport();
	void EndAttack();


	class AActor* CurrentPointToPatrolTo;

	float AttackCooldown = 2.0f;

	float CurrentTimer = 0.0f;
};



