// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayEffectComponent.h"
#include "GameplayEffectTypes.h"
#include "CancelOut.generated.h"


/**
 * 
 */
USTRUCT()
struct FGameplayEffectCancelInfo
{
	GENERATED_BODY()
	FGameplayTagRequirements TagRequirements;
	TArray<FGameplayEffectCue> Cue;
};

/**
 *
 **/
UCLASS()
class PROJECTVORTEX_API UCancelOut : public UGameplayEffectComponent
{
	GENERATED_BODY()

public:
	/** Constructor to set EditorFriendlyName */
	UCancelOut();

	/** Can we apply to the ActiveGEContainer? */
	virtual bool CanGameplayEffectApply(const FActiveGameplayEffectsContainer& ActiveGEContainer,
	                                    const FGameplayEffectSpec& GESpec) const override;

	/** Once we've applied, we need to register for ongoing requirements */
	virtual bool OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& GEContainer,
	                                         FActiveGameplayEffect& ActiveGE) const override;

#if WITH_EDITOR
	/**
	 * Validate incompatible configurations
	 */
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif // WITH_EDITOR

private:
	/** We need to be notified when we're removed to unregister some callbacks */
	void OnGameplayEffectRemoved(const FGameplayEffectRemovalInfo& GERemovalInfo, UAbilitySystemComponent* ASC,
	                             TArray<TTuple<FGameplayTag, FDelegateHandle>> AllBoundEvents) const;

	/** We need to register a callback for when the owner changes its tags.  When that happens, we need to figure out if our GE should continue to execute */
	void OnTagChanged(const FGameplayTag GameplayTag, int32 NewCount, FActiveGameplayEffectHandle ActiveGEHandle) const;

public:
	UPROPERTY(EditDefaultsOnly, Category = Tags)
	FGameplayTagRequirements CancelTagRequirements;
};
