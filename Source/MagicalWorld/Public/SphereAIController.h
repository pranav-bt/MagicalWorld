// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicAIController.h"
#include "SphereAIController.generated.h"

/**
 * 
 */
UCLASS()
class MAGICALWORLD_API ASphereAIController : public AMagicAIController
{
	GENERATED_BODY()
	
public:
	class ASphereEnemyCharacter* SphereCharacter;

	enum SphereState
	{
		Idle,
		Rush,
		Melee,
		Blast
	};

	SphereState CurrentState;
	SphereState PreviousState;
	SphereState NextState;

	void ChangeState();

	void UpdateState();

	//State Functions

	void BeginRush();
	void BeginMelee();
	void BeginBlast();

	void UpdateRush();
	void UpdateMelee();
	void UpdateBlast();

	void EndRush();
	void EndMelee();
	void EndBlast();

	float CurrentMeleeTimer = 0.0f;

	float TimeToPlayBlastVFX = 0.7f;
};
