// Fill out your copyright notice in the Description page of Project Settings.


#include "GiveAbility.h"
#include "../MagicalWorldCharacter.h"
#include "MagicSystemComponent.h"
#include "MagicSpell.h"

// Sets default values
AGiveAbility::AGiveAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(15.0f);
	// Set the root component to be the collision component.
	RootComponent = CollisionComponent;
}

// Called when the game starts or when spawned
void AGiveAbility::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AGiveAbility::OnCollision);
}

// Called every frame
void AGiveAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGiveAbility::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMagicalWorldCharacter>(OtherActor) && !GiveMana)
	{
		Cast<AMagicalWorldCharacter>(OtherActor)->MagicSystemComponent->AddNewSpell(MagicSpellToGive);
		this->K2_DestroyActor();
	}

	else if (Cast<AMagicalWorldCharacter>(OtherActor))
	{
		Cast<AMagicalWorldCharacter>(OtherActor)->MagicSystemComponent->UpdateMana(ManaToGive);
		this->K2_DestroyActor();
	}
}

