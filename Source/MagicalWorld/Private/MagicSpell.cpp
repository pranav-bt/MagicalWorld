// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicSpell.h"
#include "SpellData.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "EnemyActor.h"
#include "EnemyCharacter.h"
#include "../MagicalWorldCharacter.h"
#include "GameplayTagContainer.h"

// Sets default values
AMagicSpell::AMagicSpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	PlayerCharacter = Cast<AMagicalWorldCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

// Called when the game starts or when spawned
void AMagicSpell::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMagicSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Initialized)
	{
		Spawnedparticle = UGameplayStatics::SpawnEmitterAttached(SpellEffectt,RootComponent);

		if (Spawnedparticle && CurrentSpellMode == Homing)
		{
			AActor* Target = UGameplayStatics::GetActorOfClass(GetWorld(), HomingTarget);
			ProjectileMovementComponent->bIsHomingProjectile = true;
			ProjectileMovementComponent->HomingAccelerationMagnitude = ProjectileMovementComponent->MaxSpeed * 1.5;
			if (Target)
			{
				ProjectileMovementComponent->HomingTargetComponent = Target->GetRootComponent();
			}
			else
			{
				CurrentSpellMode = Normal;
			}
		}

		if (Spawnedparticle && CurrentSpellMode == Normal)
		{
			FireInDirection(PlayerCharacter->GetActorForwardVector());
		}

		if (Spawnedparticle && CurrentSpellMode == AOE)
		{
			
		}

		if (Spawnedparticle && CurrentSpellMode == Custom)
		{

		}
		Initialized = false;
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMagicSpell::OnCollisionOfSpell);
	}
	
	TArray<AActor*> Enemies;
	switch (CurrentSpellMode)
	{
	case Normal:
		if (FVector::Dist(PlayerCharacter->GetActorLocation(), this->GetActorLocation()) > Rangee)
		{
			CollisionComponent->OnComponentBeginOverlap.RemoveDynamic(this, &AMagicSpell::OnCollisionOfSpell);
			this->K2_DestroyActor();
		}
		break;
	case Homing:
		if (OwnerOfSpell == Enemy)
		{
			HomingTimer -= GetWorld()->DeltaTimeSeconds;
			if (HomingTimer <= 0.0f)
			{
				CollisionComponent->OnComponentBeginOverlap.RemoveDynamic(this, &AMagicSpell::OnCollisionOfSpell);
				this->K2_DestroyActor();
			}
		}
		break;
	case AOE:
		if (OwnerOfSpell == Player)
		{
			AOETimer -= GetWorld()->DeltaTimeSeconds;

			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseEnemyCharacter::StaticClass(), Enemies);
			if (Enemies.Num() != 0 && !OnceAOE)
			{
				for (int i = 0; i < Enemies.Num(); i++)
				{
					if (FVector::Dist(Enemies[i]->GetActorLocation(), PlayerCharacter->GetActorLocation()) < AOERangee)
					{
						if (Cast<ABaseEnemyCharacter>(Enemies[i]))
						{
							Cast<ABaseEnemyCharacter>(Enemies[i])->DealDamage(Damagee);
						}
					}
					OnceAOE = true;
				}
			}
			if (AOETimer <= 0.0f)
			{
				CollisionComponent->OnComponentBeginOverlap.RemoveDynamic(this, &AMagicSpell::OnCollisionOfSpell);
				this->K2_DestroyActor();
			}
		}
		break;
	case Custom:
	default:
		break;
	}
}

void AMagicSpell::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AMagicSpell::InitializeMagicSpell()
{
		if (TypeOfSpelll.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Spell.Normal"))))
		{
			CurrentSpellMode = Normal;
		}
		if (TypeOfSpelll.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Spell.Homing"))))
		{
			CurrentSpellMode = Homing;
		}
		if (TypeOfSpelll.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Spell.AOE"))))
		{
			CurrentSpellMode = AOE;
		}
		if (TypeOfSpelll.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Spell.Custom"))))
		{
			CurrentSpellMode = Custom;
		}
		Initialized = true;
}


void AMagicSpell::OnCollisionOfSpell(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OwnerOfSpell == Player && Cast<ABaseEnemyCharacter>(OtherActor))
	{
		CollisionComponent->OnComponentBeginOverlap.RemoveDynamic(this, &AMagicSpell::OnCollisionOfSpell);
		this->K2_DestroyActor();
		Cast<ABaseEnemyCharacter>(OtherActor)->DealDamage(Damagee);
	}

	if (OwnerOfSpell == Enemy && Cast<AMagicalWorldCharacter>(OtherActor))
	{
		CollisionComponent->OnComponentBeginOverlap.RemoveDynamic(this, &AMagicSpell::OnCollisionOfSpell);
		this->K2_DestroyActor();
		Cast<AMagicalWorldCharacter>(OtherActor)->DealDamage(Damagee);
	}
}


