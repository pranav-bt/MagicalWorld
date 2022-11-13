// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GiveAbility.generated.h"

UCLASS()
class MAGICALWORLD_API AGiveAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGiveAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere collision component.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		USphereComponent* CollisionComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AMagicSpell> MagicSpellToGive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool GiveMana = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 ManaToGive = 50;

	UFUNCTION()
		void OnCollision(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

};
