// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CustomAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVORTEX_API UCustomAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UCustomAbilitySystemComponent();
	
	bool bDefaultabilitiesGiven = false;
	
	bool bDefaultEffectsApplied = false;

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool HasAbility(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAbilitySpecHandle Ability);
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool HasAbilityClass(TSubclassOf<UGameplayAbility> InAbility, FGameplayAbilitySpecHandle &OutAbilitySpecHandle);
};
