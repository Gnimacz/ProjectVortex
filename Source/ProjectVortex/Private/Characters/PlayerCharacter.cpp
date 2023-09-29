// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVortex/Public/Characters/PlayerCharacter.h"

#include "ProjectVortex/Public/GameplayAbilities/AbilityInputBindings.h"
#include "ProjectVortex/Public/GameplayAbilityComponent/CustomAbilitySystemComponent.h"
#include "ProjectVortex/Public/PlayerState/PlayerStateBase.h"

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (APlayerStateBase* PlayerStateBase = Cast<APlayerStateBase>(GetPlayerState()))
	{
		AbilitySystemComponent = PlayerStateBase->AbilitySystemComponent;

		//ADD EXTRA ATTRIBUTE SETS HERE
		// Set the Owner and Avatar actor for the Ability System Component. (On the Server)
		AbilitySystemComponent->InitAbilityActorInfo(PlayerStateBase, this);

		HealthAttributes = PlayerStateBase->HealthAttributes;
		MovementSpeedAttributes = PlayerStateBase->MovementSpeedAttributes;
		// MovementSpeedAttributes = PlayerStateBase->MovementSpeedAttributes;		

		GiveDefaultAbilities();

		ApplyDefaultEffects();
	}
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if (APlayerStateBase* PlayerStateBase = Cast<APlayerStateBase>(GetPlayerState()))
	{
		AbilitySystemComponent = PlayerStateBase->AbilitySystemComponent;

		//ADD EXTRA ATTRIBUTE SETS HERE
		// Set the Owner and Avatar actor for the Ability System Component. (On the Client)
		AbilitySystemComponent->InitAbilityActorInfo(PlayerStateBase, this);

		HealthAttributes = PlayerStateBase->HealthAttributes;

		MovementSpeedAttributes = PlayerStateBase->MovementSpeedAttributes;

		InitializeAbilityBindings();
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InitializeAbilityBindings();
}

void APlayerCharacter::InitializeAbilityBindings()
{
	if (AbilityBindingsInitialized || !GetPlayerState() || !AbilitySystemComponent.Get() || !InputComponent)
	{
		return;
	}

	// Binds GA input to the Input component.
	// These input bindings can be edited in "GameplayAbilityBindings.h" (Do not remove "None", "Confirm", or "Cancel")
	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent,
	                                                              FGameplayAbilityInputBinds(
		                                                              FString("ConfirmTarget"), FString("CancelTarget"),
		                                                              FString("EGameplayAbilityBindings"),
		                                                              static_cast<int32>(
			                                                              EGameplayAbilityBindings::Confirm),
		                                                              static_cast<int32>(
			                                                              EGameplayAbilityBindings::Cancel)));

	AbilityBindingsInitialized = true;
}