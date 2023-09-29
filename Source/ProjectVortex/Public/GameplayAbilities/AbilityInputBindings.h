// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayAbilitySpec.h"
#include "EnhancedInputComponent.h"
#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameplayAbilityBindings : uint8
{
 None				UMETA(DisplayName = "None"),
	
 Confirm			UMETA(DisplayName = "Confirm"),

 Cancel			UMETA(DisplayName = "Cancel"),

 Ability1			UMETA(DisplayName = "Ability1"),

 Ability2			UMETA(DisplayName = "Ability2"),

 Ability3			UMETA(DisplayName = "Ability3"),

 Ability4			UMETA(DisplayName = "Ability4"),

 Ability5			UMETA(DisplayName = "Ability5"),

 Sprint			UMETA(DisplayName = "Sprint"),

 Jump			UMETA(DisplayName = "Jump")
};
