// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Attribute_Sets/HealthAttributeSet.h"
#include "Attribute_Sets/ManaAttributeSet.h"
#include "Attribute_Sets/MovementSpeedAttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

/**
 * 
 */

class UCustomAbilitySystemComponent;

UCLASS()
class PROJECTVORTEX_API APlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerStateBase();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ability System")
	UCustomAbilitySystemComponent* AbilitySystemComponent;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	UHealthAttributeSet* HealthAttributes;

	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	UMovementSpeedAttributeSet* MovementSpeedAttributes;

	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	UManaAttributeSet* ManaAttributes;

};
