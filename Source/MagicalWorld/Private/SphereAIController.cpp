// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereAIController.h"
#include "Kismet/GameplayStatics.h"
#include "../MagicalWorldCharacter.h"
#include "SphereEnemyCharacter.h"
#include "MagicSpell.h"

void ASphereAIController::ChangeState()
{

	switch (CurrentState)
	{
	case Idle:
	case Rush:
		EndRush();
		break;
	case Melee:
		EndMelee();
		break;
	case Blast:
		EndBlast();
	}

	CurrentState = NextState;

	switch (CurrentState)
	{
	case Idle:
		break;
	case Rush:
		BeginRush();
		break;
	case Melee:
		BeginMelee();
		break;
	case Blast:
		BeginBlast();
		break;
	}
}

void ASphereAIController::UpdateState()
{
	switch (CurrentState)
	{
	case Idle:
		break;
	case Rush:
		UpdateRush();
		break;
	case Melee:
		UpdateMelee();
		break;
	case Blast:
		UpdateBlast();
		break;
	}
}

void ASphereAIController::BeginRush()
{
}

void ASphereAIController::BeginMelee()
{
	CurrentMeleeTimer = 0.0f;
}

void ASphereAIController::BeginBlast()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SphereCharacter->SpellEffectt, SphereCharacter->GetActorTransform());
	Cast<AMagicalWorldCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->DealDamage(40);
	SphereCharacter->bBlastStarted = true;
}

void ASphereAIController::UpdateRush()
{
	MoveToActor(Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));
}

void ASphereAIController::UpdateMelee()
{
	CurrentMeleeTimer += GetWorld()->DeltaTimeSeconds;
	if (CurrentMeleeTimer >= SphereCharacter->Cooldown && Cast<AMagicalWorldCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		SphereCharacter->ChangeToAttackMaterial(1.5f);
		Cast<AMagicalWorldCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->DealDamage(5);
		CurrentMeleeTimer = 0.0f;	
	}
}

void ASphereAIController::UpdateBlast()
{
	TimeToPlayBlastVFX -= GetWorld()->DeltaTimeSeconds;
	if (TimeToPlayBlastVFX < 0.0f)
	{
		SphereCharacter->DealDamage(100.0f);
	}
}

void ASphereAIController::EndRush()
{
}

void ASphereAIController::EndMelee()
{
}

void ASphereAIController::EndBlast()
{
}
