// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeAIController.h"
#include "EnemyCharacter.h"
#include "MagicSpell.h"

void ACubeAIController::ChangeState()
{
	switch (CurrentState)
	{
	case Idle:
	case Patrol:
		EndPatrol();
	case Attack:
		EndAttack();
	case Teleport:
		EndTeleport();
	}

	CurrentState = NextState;

	switch (CurrentState)
	{
	case Idle:
		break;
	case Patrol:
		BeginPatrol(); 
		break;
	case Attack:
		BeginAttack();
		break;
	case Teleport:
		BeginTeleport();
		break;
	}
}

void ACubeAIController::UpdateState()
{
	switch (CurrentState)
	{
	case Idle:
		break;
	case Patrol:
		UpdatePatrol();
		break;
	case Attack:
		UpdateAttack();
		break;
	case Teleport:
		UpdateTeleport();
		break;
	}
}

void ACubeAIController::BeginPatrol()
{
	MoveToNextPoint();
}

void ACubeAIController::MoveToNextPoint()
{
	CurrentPointToPatrolTo = CubeCharacter->PatrolPoints[FMath::RandRange(0, CubeCharacter->PatrolPoints.Num() - 1)];
	if (CurrentPointToPatrolTo)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "Moving");
		MoveToActor(CurrentPointToPatrolTo);
	}
}

void ACubeAIController::BeginTeleport()
{
	auto PatrolActor = CubeCharacter->TeleportPoints[FMath::RandRange(0, CubeCharacter->PatrolPoints.Num() - 1)];
	CubeCharacter->TeleportTo(PatrolActor->GetActorLocation(), PatrolActor->GetActorRotation());
}

void ACubeAIController::BeginAttack()
{
	ShootSpell();
}

void ACubeAIController::ShootSpell()
{
	FActorSpawnParameters SpawnParams;
	AMagicSpell* Projectile = GetWorld()->SpawnActor<AMagicSpell>(CubeCharacter->EnemySpell, CubeCharacter->GetActorLocation(), CubeCharacter->GetActorRotation(), SpawnParams);
	if (Projectile)
	{
		Projectile->InitializeMagicSpell();
		AttackCooldown = CubeCharacter->EnemySpell.GetDefaultObject()->Cooldownn;
		CurrentTimer = 0.0f;
	}
}

void ACubeAIController::UpdatePatrol()
{
	if (FVector::Dist(CurrentPointToPatrolTo->GetActorLocation(), CubeCharacter->GetActorLocation()) < 100.0f)
	{
		CurrentPointToPatrolTo = CubeCharacter->PatrolPoints[FMath::RandRange(0, CubeCharacter->PatrolPoints.Num() - 1)];
		if (CurrentPointToPatrolTo)
		{
			MoveToActor(CurrentPointToPatrolTo);

		}
	}
}

void ACubeAIController::UpdateTeleport()
{
}

void ACubeAIController::UpdateAttack()
{
	CurrentTimer += GetWorld()->DeltaTimeSeconds;
	if (CurrentTimer >= AttackCooldown)
	{
		ShootSpell();
	}
}

void ACubeAIController::EndPatrol()
{
}

void ACubeAIController::EndTeleport()
{
}

void ACubeAIController::EndAttack()
{
}
