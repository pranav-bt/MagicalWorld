#include "MagicSystemComponent.h"
#include "MagicSpell.h"
#include "Kismet/GameplayStatics.h"
#include "../MagicalWorldCharacter.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicSystemComponent.h"

// Sets default values for this component's properties
UMagicSystemComponent::UMagicSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMagicSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AMagicalWorldCharacter>(GetOwner());
	SpellCooldowns.Init(0, 8);
	PlayerCharacter->GameHUD->SetMana(Mana);
	AudioComponent = NewObject<UAudioComponent>(this);
	// ...
	
}


// Called every frame
void UMagicSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

void UMagicSystemComponent::UpdateMana(int32 Manareceived)
{
	Mana += Manareceived;
	PlayerCharacter->GameHUD->SetMana(Mana);
}

bool UMagicSystemComponent::HasEnoughMana()
{
	if (Mana - MagicSpells[ActiveSpellIndex].GetDefaultObject()->ManaToConsume < 0)
	{
		return false;
	}
	return true;
}

void UMagicSystemComponent::ConsumeMana(int32 ManaToConsume)
{
	Mana -= ManaToConsume;
}

void UMagicSystemComponent::ResetCooldown(int32 SpellIndex)
{
	SpellCooldowns[SpellIndex - 1] = 0;
}

void UMagicSystemComponent::CastSpell()
{
	if (!HasEnoughMana() )
	{
		if (NoManaSFX)
		{
			AudioComponent->SetSound(NoManaSFX);
			AudioComponent->Play();
		}
		return;
	}
	if (ActiveSpellIndex < MagicSpells.Num() && SpellCooldowns[ActiveSpellIndex] <= 0 && HasEnoughMana())
	{
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		FVector MuzzleOffset;
		PlayerCharacter->GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// Skew the aim to be slightly upwards.
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = PlayerCharacter;
			SpawnParams.Instigator = PlayerCharacter->GetInstigator();

			// Spawn the projectile at the muzzle.
			AMagicSpell* Projectile = World->SpawnActor<AMagicSpell>(MagicSpells[ActiveSpellIndex], PlayerCharacter->GetMesh()->GetSocketLocation(FName("Muzzle_01")), MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				Projectile->InitializeMagicSpell();
				SpellCooldowns[ActiveSpellIndex] = MagicSpells[ActiveSpellIndex].GetDefaultObject()->Cooldownn;
				PlayerCharacter->GameHUD->ApplyCooldown(this, ActiveSpellIndex+1, Projectile->Cooldownn);
				ConsumeMana(Projectile->ManaToConsume);
				PlayerCharacter->GameHUD->SetMana(Mana);
				if (Projectile->SpellSoundEffect)
				{
					AudioComponent->SetSound(Projectile->SpellSoundEffect);
					AudioComponent->Play();
				}
			}
		}
	}
}

void UMagicSystemComponent::AddNewSpell(TSubclassOf<class AMagicSpell> SpellToAdd)
{
	MagicSpells.Add(SpellToAdd);
	if (GetNewSpellSFX)
	{
		AudioComponent->SetSound(GetNewSpellSFX);
		AudioComponent->Play();
	}
}

void UMagicSystemComponent::ChangeActiveSpell(int32 Index)
{
	if (MagicSpells.Num()<Index)
	{
		PlayerCharacter->GameHUD->SpellNotValid(Index);
		return;
	}
	PlayerCharacter->GameHUD->SetCurrentMagicSpell(Index);
	ActiveSpellIndex = Index - 1;
}

