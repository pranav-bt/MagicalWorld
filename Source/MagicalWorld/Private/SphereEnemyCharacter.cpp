// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereEnemyCharacter.h"
#include "Components/WidgetComponent.h"
#include "MagicSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SphereAIController.h"
#include "../MagicalWorldCharacter.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ASphereEnemyCharacter::ASphereEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	HealthText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthText"));
	HealthText->SetupAttachment(EnemyWidget);
}

// Called when the game starts or when spawned
void ASphereEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<ASphereAIController>(Controller);
	AIController->SphereCharacter = this;
	AIController->CurrentState = AIController->Idle;
	AIController->NextState = AIController->Idle;
}

// Called every frame
void ASphereEnemyCharacter::Tick(float DeltaTime)
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
void ASphereEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASphereEnemyCharacter::DealDamage(int32 Damage)
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
			this->K2_DestroyActor();
		}
	}
}

void ASphereEnemyCharacter::ChangeStateConditions()
{
	if (!bBlastStarted)
	{
		auto dis = FVector::Dist(UGameplayStatics::GetActorOfClass(GetWorld(), AMagicalWorldCharacter::StaticClass())->GetActorLocation(), GetActorLocation());
		if (Health < 30.0f && dis < 125.0f)
		{
			AIController->NextState = AIController->Blast;
			bBlastStarted = true;
			return;
		}

		if (dis < 200.0f)
		{
			AIController->NextState = AIController->Melee;
			return;
		}

		if (dis < 1000.0f)
		{
			AIController->NextState = AIController->Rush;
			return;
		}
	}
}

