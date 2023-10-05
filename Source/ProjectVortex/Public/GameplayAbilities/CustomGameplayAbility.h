// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityInputBindings.h"
#include "Abilities/GameplayAbility.h"
#include "Data/GameplayAbilitySystemData.h"
#include "CustomGameplayAbility.generated.h"

enum class EAttributeSearchType : uint8;
class UInputAction;
class UCustomAbilitySystemComponent;

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAbilityModifierStruct
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayAttribute BackingAttribute;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EAttributeSearchType AttributeSearchType = EAttributeSearchType::BaseValue;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float AttributeModifier = 1;
};

UCLASS()
class PROJECTVORTEX_API UCustomGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UCustomGameplayAbility();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability Input")
	UInputAction* AbilityInputAction;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability Input")
	EGameplayAbilityBindings InputBinding = EGameplayAbilityBindings::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability Input")
	bool ActivateAbilityOnGranted = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modifiers")
	FScalableFloat BaseAbilityStrength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modifiers")
	TArray<FAbilityModifierStruct> AbilityModifiers;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Custom Gameplay Ability|Modifiers")
	float GetModifiedAbilityStrength();

	virtual void K2_EndAbility() override;

protected:
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
};
