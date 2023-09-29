// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTVORTEX_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	
protected:

	// Called on the server to acknowledge possession of this Character.
	virtual void PossessedBy(AController* NewController) override;

	// Called on the client when the Character is assigned it's Player State.
	virtual void OnRep_PlayerState() override;

	// Called to bind input to this Character.
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Called to set-up Ability input bindings for this Character.
	void InitializeAbilityBindings();

	bool AbilityBindingsInitialized = false;
};