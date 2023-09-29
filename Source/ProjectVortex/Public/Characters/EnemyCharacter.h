// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTVORTEX_API AEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Ability System")
	class UCustomAbilitySystemComponent* Enemy_AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Ability System")
	class UHealthAttributeSet* Enemy_HealthAttributes;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Ability System")
	class UMovementSpeedAttributeSet* Enemy_MovementSpeedAttributeSet;

	virtual void BeginPlay() override;
};
