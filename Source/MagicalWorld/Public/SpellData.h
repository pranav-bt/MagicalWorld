// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Particles/ParticleSystem.h"
#include "GameplayTagContainer.h"
#include "SpellData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MAGICALWORLD_API USpellData : public UObject
{
	GENERATED_BODY()


public:

		// The vfx or effect to be played when spell is cast. 
		UPROPERTY(EditAnywhere)
		UParticleSystem* SpellEffect;

		UPROPERTY(EditAnywhere)
		float Damage;

		UPROPERTY(EditAnywhere)
		float Range;

		UPROPERTY(EditAnywhere)
		float Cooldown;

		UPROPERTY(EditAnywhere)
		FGameplayTag TypeOfSpell;
};
