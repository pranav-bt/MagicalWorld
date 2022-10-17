// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicSpell.h"
#include "SpellData.h"
#include "Spell_DamageOrb.generated.h"

/**
 * 
 */
UCLASS()
class MAGICALWORLD_API ASpell_DamageOrb : public AMagicSpell
{
	GENERATED_BODY()

public:

	ASpell_DamageOrb();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USpellData> SpellDta;
	
};
