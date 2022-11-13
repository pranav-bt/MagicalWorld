// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MagicSpell.h"
#include "BaseEnemyCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/Material.h"
#include "SphereEnemyCharacter.generated.h"

UCLASS()
class MAGICALWORLD_API ASphereEnemyCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASphereEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* EnemyWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* HealthText;

	void DealDamage(int32 Damage);

	int32 Health = 100;

	class ASphereAIController* AIController;

	void ChangeStateConditions();

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AMagicSpell> EnemySpell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UMaterial* AttackMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UMaterial* RegularMaterial;

	UPROPERTY(EditAnywhere, category = "Attack")
	UParticleSystem* SpellEffectt;

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeToAttackMaterial(float Duration);

	float Cooldown = 1.5f;

	bool bBlastStarted = false;
};
