// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/MagicSpell.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Public/MagicalWorldUserWidget.h"
#include "MagicalWorldCharacter.generated.h"

UCLASS(config=Game)
class AMagicalWorldCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMagicalWorldCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMagicalWorldUserWidget* GameHUD;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MagicSpell, meta = (AllowPrivateAccess = "true"))
	class UMagicSystemComponent* MagicSystemComponent;


	UFUNCTION(BlueprintCallable)
	void AddHealth(int32 Health);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MagicSystem)
	TArray<TSubclassOf<AMagicSpell>> MagicSpells;


	void FireDamageOrb();

	void Spell1Equip();

	void Spell2Equip();

	void Spell3Equip();

	void DealDamage(int32 Damage);

	int32 Health = 100;

	UPROPERTY(BlueprintReadWrite)
	int32 MaxDungeonsToCreate = 6;

	int32 CurrentDungeons = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 EnemiesKilled = 0;
};

