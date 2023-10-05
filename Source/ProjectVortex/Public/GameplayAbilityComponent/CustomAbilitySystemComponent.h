// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CustomAbilitySystemComponent.generated.h"

struct FPredictionKey;

/**
 * 
 */

UENUM(BlueprintType)
enum class EBranchEnum : uint8
{
	Pressed UMETA(DisplayName = "Pressed"),
	Released UMETA(DisplayName = "Released"),
};

/**
 * 
 */

UENUM(BlueprintType)
enum class EOutputBranchEnum : uint8
{
	OnPressed UMETA(DisplayName = "Pressed"),
	OnReleased UMETA(DisplayName = "Released"),
};

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class PROJECTVORTEX_API UCustomAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UCustomAbilitySystemComponent();

	bool bDefaultabilitiesGiven = false;

	bool bDefaultEffectsApplied = false;

	// UFUNCTION(BlueprintCallable, Category = "Ability System|Gameplay Cue", meta = (AutoCreateRefTerm = "GameplayCueParameters", AdvancedDisplay = "GameplayCueParameters", DisplayName = "AddGameplayCue"))
	// void AddGameplayCue_Internal(const FGameplayTag GameplayCueTag, FGameplayEffectContextHandle& EffectContext, FActiveGameplayCueContainer& GameplayCueContainer) override;
	// UFUNCTION(BlueprintCallable, Category = "Ability System|Gameplay Cue", meta = (AutoCreateRefTerm = "GameplayCueParameters", AdvancedDisplay = "GameplayCueParameters", DisplayName = "AddGameplayCue"))
	// void AddGameplayCue_Internal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters, FActiveGameplayCueContainer& GameplayCueContainer) override;
	//

	FGameplayAbilitySpec* HasAbility(TSubclassOf<UGameplayAbility> AbilityToCheck);
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool HasAbilityClass(TSubclassOf<UGameplayAbility> AbilityToCheck,
	                     FGameplayAbilitySpecHandle& FoundAbilitySpecHandle);
	/*
	* Looks for the ability that's given and tries to activate it.
	* Returns whether the input key was pressed(True) or released(False).
	 */
	UFUNCTION(BlueprintCallable, Category = "Ability System",
		meta = (ExpandEnumAsExecs = "Activation", ExpandBoolAsExecs = "WasReleased"))
	void ActivateAbilityByClass(bool& WasReleased, TEnumAsByte<EBranchEnum> Activation,
	                            TSubclassOf<UGameplayAbility> AbilityToActivate, bool bAllowRemoteActivation = true);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	int UpgradeAbility(TSubclassOf<UGameplayAbility> AbilityToUpgrade, int Level , FGameplayAbilitySpecHandle& UpgradedAbilityHandle);
};
