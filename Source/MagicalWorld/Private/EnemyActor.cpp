// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/WidgetComponent.h"
#include "MagicSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../MagicalWorldCharacter.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	HealthText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthText"));
	HealthText->SetupAttachment(EnemyWidget);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyActor::DealDamage(int32 Damage)
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

