// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectVortex/Public/Attribute_Sets/ManaAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "ProjectVortex/Public/Characters/CharacterBase.h"
#include "Net/UnrealNetwork.h"

UManaAttributeSet::UManaAttributeSet()
{
	MaximumMana = 0.0f;
	CurrentMana = 0.0f;
	ManaRegeneration = 0.0f;
}

void UManaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaximumManaAttribute())
	{
		AdjustAttributeForMaxChange(CurrentMana, MaximumMana, NewValue, GetCurrentManaAttribute());
	}
}

void UManaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetManaDrainAttribute())
	{
		const float manaDrained = GetManaDrain();

		SetManaDrain(0.0f);

		if(manaDrained > 0.0f)
		{
			const float NewMana = GetCurrentMana() - manaDrained;

			SetCurrentMana(FMath::Clamp(NewMana, 0.0f, GetMaximumMana()));
		}
	}
	else if(Data.EvaluatedData.Attribute == GetRegenerationAttribute())
	{
		const float LocalRegenerationDone = GetManaRegeneration();

		SetRegeneration(0.0f);
		
		if(LocalRegenerationDone > 0.0f)
		{
			const float NewMana = GetCurrentMana() + LocalRegenerationDone;
			SetCurrentMana(FMath::Clamp(NewMana, 0.0f, GetMaximumMana()));

			if(ACharacterBase* AvatarCharacter = Cast<ACharacterBase>(Data.Target.GetAvatarActor()))
			{
				AvatarCharacter->OnManaRegen();
			}
		}
	}
	else if(Data.EvaluatedData.Attribute == GetCurrentManaAttribute())
	{
		SetCurrentMana(FMath::Clamp(GetCurrentMana(), 0.0f, GetMaximumMana()));
	}
	else if(Data.EvaluatedData.Attribute == GetManaRegenerationAttribute())
	{
		SetManaRegeneration(FMath::Clamp(GetManaRegeneration(), 0.0f, GetMaximumMana()));
	}
}


void UManaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, CurrentMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, MaximumMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
}

void UManaAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
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

void UManaAttributeSet::OnRep_CurrentMana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, CurrentMana, OldMana);
}

void UManaAttributeSet::OnRep_MaximumMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, MaximumMana, OldMaxMana);
}

void UManaAttributeSet::OnRep_Regeneration(const FGameplayAttributeData& OldManaRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, ManaRegeneration, OldManaRegeneration);
}
