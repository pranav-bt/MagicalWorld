// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MagicalWorldUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAGICALWORLD_API UMagicalWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category="Cooldown")
	void ApplyCooldown(class UMagicSystemComponent* MagicSystem, int32 PowerIndex, float CooldownTimer);

	UFUNCTION(BlueprintImplementableEvent, Category = "Cooldown")
	void EndCooldown(int32 PowerIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Cooldown")
	void SetCurrentMagicSpell(int32 PowerIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Attributes")
	void SetMana(int32 NewMana);

	UFUNCTION(BlueprintImplementableEvent, Category = "Attributes")
	void Sethealth(int32 NewHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "Attributes")
	void SpellNotValid(int32 PowerIndex);
};
