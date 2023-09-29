// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVortex/Public/Attribute_Sets/MovementSpeedAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "ProjectVortex/Public/Characters/CharacterBase.h"
#include "Net/UnrealNetwork.h"

UMovementSpeedAttributeSet::UMovementSpeedAttributeSet()
{
	MaximumMoveSpeed = 0.0f;
	CurrentMoveSpeed = 0.0f;
}

void UMovementSpeedAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaximumMoveSpeedAttribute())
	{
		AdjustAttributeForMaxChange(CurrentMoveSpeed, MaximumMoveSpeed, NewValue, GetCurrentMoveSpeedAttribute());
	}
}

void UMovementSpeedAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	

	if(Data.EvaluatedData.Attribute == GetCurrentMoveSpeedAttribute())
	{
		SetCurrentMoveSpeed(FMath::Clamp(GetCurrentMoveSpeed(), 0.0f, GetMaximumMoveSpeed()));
	}
}

void UMovementSpeedAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMovementSpeedAttributeSet, CurrentMoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMovementSpeedAttributeSet, MaximumMoveSpeed, COND_None, REPNOTIFY_Always);
}

void UMovementSpeedAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
                                                      const FGameplayAttributeData& MaxAttribute, float NewMaxValue,
                                                      const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilitySystemComponent = GetOwningAbilitySystemComponent();
	
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();

	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilitySystemComponent)
	{
		// Change current value to maintain the Current Value / Maximum Value percentage.
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		const float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilitySystemComponent->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UMovementSpeedAttributeSet::OnRep_CurrentMoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMovementSpeedAttributeSet, CurrentMoveSpeed, OldMoveSpeed);
}

void UMovementSpeedAttributeSet::OnRep_MaximumMoveSpeed(const FGameplayAttributeData& OldMaxMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMovementSpeedAttributeSet, MaximumMoveSpeed, OldMaxMoveSpeed);
}
