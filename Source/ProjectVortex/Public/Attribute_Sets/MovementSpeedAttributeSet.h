// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MovementSpeedAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROJECTVORTEX_API UMovementSpeedAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UMovementSpeedAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Blueprintreadonly, Category = "Movement Speed Attribute Set", ReplicatedUsing = OnRep_CurrentMoveSpeed)
	FGameplayAttributeData CurrentMoveSpeed;
	ATTRIBUTE_ACCESSORS(UMovementSpeedAttributeSet, CurrentMoveSpeed);

	UPROPERTY(Blueprintreadonly, Category = "Movement Speed Attribute Set", ReplicatedUsing = OnRep_MaximumMoveSpeed)
	FGameplayAttributeData MaximumMoveSpeed;
	ATTRIBUTE_ACCESSORS(UMovementSpeedAttributeSet, MaximumMoveSpeed);



protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute,
		float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	UFUNCTION()
	virtual void OnRep_CurrentMoveSpeed(const FGameplayAttributeData& OldMovementSpeed);

	UFUNCTION()
	virtual void OnRep_MaximumMoveSpeed(const FGameplayAttributeData& OldMaxMaxMovementSpeed);
	
	
};
