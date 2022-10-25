// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "GameplayTagContainer.h"
#include "EnemyActor.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MagicSpell.generated.h"

class USpellData;
class AMagicalWorldCharacter;

enum SpellMode
{
	Normal,
	Homing,
	AOE
};

UENUM()
enum SpellOwner
{
	Enemy,
	Player
};

UCLASS()
class MAGICALWORLD_API AMagicSpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicSpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;



	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

	void InitializeMagicSpell();

	bool IsAvailable = true;

	bool Initialized = false;

	float AOETimer = 4.0f;

	UParticleSystemComponent* Spawnedparticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USpellData> SpellData;

	UPROPERTY(EditAnywhere, category = "General")
		TEnumAsByte<SpellOwner> OwnerOfSpell;

	// The vfx or effect to be played when spell is cast. 
	UPROPERTY(EditAnywhere, category = "General")
		UParticleSystem* SpellEffectt;

	UPROPERTY(EditAnywhere, category="General")
		float Damagee;

	UPROPERTY(EditAnywhere, category = "General")
		float Rangee;

	UPROPERTY(EditAnywhere, category = "AOE")
		float AOERangee;

	UPROPERTY(EditAnywhere, category = "General")
		float Cooldownn;

	UPROPERTY(EditAnywhere, category = "General")
		FGameplayTag TypeOfSpelll;

	UPROPERTY(EditAnywhere, category = "General")
		int32 ManaToConsume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
		USoundCue* SpellSoundEffect;

	//Homing Target if the homing mode is selected. Ignore otherwise.
	UPROPERTY(EditAnywhere, category = "Homing")
		TSubclassOf<AActor> HomingTarget;

	bool OnceAOE = false;

	UFUNCTION()
	void OnCollisionOfSpell(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	SpellMode CurrentSpellMode;

	USpellData* CurrentSpellData;

	AMagicalWorldCharacter* PlayerCharacter;

	float HomingTimer = 10.0f;

};


