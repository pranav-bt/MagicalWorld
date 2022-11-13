// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/WidgetComponent.h"
#include "MagicSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CubeAIController.h"
#include "../MagicalWorldCharacter.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	HealthText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthText"));
	HealthText->SetupAttachment(EnemyWidget);
	PatrolPoints.Init(CreateDefaultSubobject<AActor>(TEXT("Actor")) , 3);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (!Controller)
	{
		SpawnDefaultController();
	}
	AIController = Cast<ACubeAIController>(Controller);
	AIController->CubeCharacter = this;
	AIController->CurrentState = AIController->Idle;
	AIController->NextState = AIController->Patrol;
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnemyWidget->SetWorldLocation(FVector(GetActorLocation().X, GetActorLocation().Y + 40, GetActorLocation().Z + 140));
	EnemyWidget->SetWorldRotation(FRotator(GetActorRotation()));

	//Check State Change Coditions
	ChangeStateConditions();

	//Change State When Required
	if (AIController->CurrentState != AIController->NextState)
	{
		AIController->ChangeState();
	}

	//Update Current State
	if (AIController->CurrentState)
	{
		AIController->UpdateState();
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::DealDamage(int32 Damage)
{
	Health -= Damage;
	HealthText->SetText(FText::FromString(FString::FromInt(Health)));
	if (Health <= 0)
	{
		if (Cast<AMagicalWorldCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			AMagicalWorldCharacter* player = Cast<AMagicalWorldCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			player->MagicSystemComponent->AudioComponent->SetSound(player->MagicSystemComponent->KillSFX);
			player->MagicSystemComponent->AudioComponent->Play();
			player->EnemiesKilled++;
			this->K2_DestroyActor();
		}
	}
}

void AEnemyCharacter::ChangeStateConditions()
{
	if (Health < HealthToTeleport && Health > 5.0f)
	{
		AIController->NextState = AIController->Teleport;
		HealthToTeleport = HealthToTeleport - HealthToTeleport / 2;
		return;
	}
	auto dis = FVector::Dist(UGameplayStatics::GetActorOfClass(GetWorld(), AMagicalWorldCharacter::StaticClass())->GetActorLocation(), GetActorLocation());
	//auto Distace = (UGameplayStatics::GetActorOfClass(GetWorld(), AMagicalWorldCharacter::StaticClass())->GetActorLocation() - GetActorLocation()).Dist();
	if (dis < AttackRange)
	{
		AIController->NextState = AIController->Attack;
		return;
	}

	AIController->NextState = AIController->Patrol;
}

