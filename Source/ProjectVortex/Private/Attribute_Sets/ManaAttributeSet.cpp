// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectVortex/Public/Attribute_Sets/ManaAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "ProjectVortex/Public/Characters/CharacterBase.h"
#include "Net/UnrealNetwork.h"

float globalNewValue = 0;

UManaAttributeSet::UManaAttributeSet()
{
	MaximumWaterMana = 0.0f;
	CurrentWaterMana = 0.0f;

	MaximumEarthMana = 0.0f;
	CurrentEarthMana = 0.0f;

	MaximumFireMana = 0.0f;
	CurrentFireMana = 0.0f;

	MaximumAirMana = 0.0f;
	CurrentAirMana = 0.0f;
	// ManaRegeneration = 0.0f;
}

void UManaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	globalNewValue = NewValue;

	if (Attribute == GetMaximumWaterManaAttribute())
	{
		AdjustAttributeForMaxChange(CurrentWaterMana, MaximumWaterMana, NewValue, GetCurrentWaterManaAttribute());
	}
	else if (Attribute == GetMaximumEarthManaAttribute())
	{
		AdjustAttributeForMaxChange(CurrentEarthMana, MaximumEarthMana, NewValue, GetCurrentEarthManaAttribute());
	}
	else if (Attribute == GetMaximumFireManaAttribute())
	{
		AdjustAttributeForMaxChange(CurrentFireMana, MaximumFireMana, NewValue, GetCurrentFireManaAttribute());
	}
	else if (Attribute == GetMaximumAirManaAttribute())
	{
		AdjustAttributeForMaxChange(CurrentAirMana, MaximumAirMana, NewValue, GetCurrentAirManaAttribute());
	}
}

void UManaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetCurrentWaterManaAttribute())
	{
		SetCurrentWaterMana(FMath::Clamp(GetCurrentWaterMana(), 0.0f, GetMaximumWaterMana()));
		if (ACharacterBase* AvatarCharacter = Cast<ACharacterBase>(Data.Target.GetAvatarActor()))
		{
			if (globalNewValue > 0)
			{
				AvatarCharacter->OnManaRegen(ManaType::Water, globalNewValue);
			}
			else if(globalNewValue <= 0)
			{
				AvatarCharacter->OnManaDrain(ManaType::Water, FMath::Abs(globalNewValue));
			}
			else if(GetCurrentWaterMana() <= 0.0f)
			{
				AvatarCharacter->OnManaEmpty(ManaType::Water);
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetCurrentEarthManaAttribute())
	{
		SetCurrentWaterMana(FMath::Clamp(GetCurrentEarthMana(), 0.0f, GetMaximumEarthMana()));
		if (ACharacterBase* AvatarCharacter = Cast<ACharacterBase>(Data.Target.GetAvatarActor()))
		{
			if (globalNewValue > 0)
			{
				AvatarCharacter->OnManaRegen(ManaType::Earth, globalNewValue);
			}
			else if(globalNewValue <= 0)
			{
				AvatarCharacter->OnManaDrain(ManaType::Earth, FMath::Abs(globalNewValue));
			}
			else if(GetCurrentEarthMana() <= 0.0f)
			{
				AvatarCharacter->OnManaEmpty(ManaType::Earth);
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetCurrentFireManaAttribute())
	{
		SetCurrentWaterMana(FMath::Clamp(GetCurrentFireMana(), 0.0f, GetMaximumFireMana()));
		if (ACharacterBase* AvatarCharacter = Cast<ACharacterBase>(Data.Target.GetAvatarActor()))
		{
			if (globalNewValue > 0)
			{
				AvatarCharacter->OnManaRegen(ManaType::Fire, globalNewValue);
			}
			else if(globalNewValue <= 0)
			{
				AvatarCharacter->OnManaDrain(ManaType::Fire, FMath::Abs(globalNewValue));
			}
			else if(GetCurrentFireMana() <= 0.0f)
			{
				AvatarCharacter->OnManaEmpty(ManaType::Fire);
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetCurrentAirManaAttribute())
	{
		SetCurrentWaterMana(FMath::Clamp(GetCurrentAirMana(), 0.0f, GetMaximumAirMana()));
		if (ACharacterBase* AvatarCharacter = Cast<ACharacterBase>(Data.Target.GetAvatarActor()))
		{
			if (globalNewValue > 0)
			{
				AvatarCharacter->OnManaRegen(ManaType::Air, globalNewValue);
			}
			else if(globalNewValue <= 0)
			{
				AvatarCharacter->OnManaDrain(ManaType::Air, FMath::Abs(globalNewValue));
			}
			if(GetCurrentAirMana() <= 0.0f)
			{
				AvatarCharacter->OnManaEmpty(ManaType::Air);
			}
		}
	}
#pragma region not used
	// if(Data.EvaluatedData.Attribute == GetManaDrainAttribute())
	// {
	// 	const float manaDrained = GetManaDrain();
	//
	// 	SetManaDrain(0.0f);
	//
	// 	if(manaDrained > 0.0f)
	// 	{
	// 		const float NewMana = GetCurrentMana() - manaDrained;
	//
	// 		SetCurrentMana(FMath::Clamp(NewMana, 0.0f, GetMaximumMana()));
	// 	}
	// }
	// else if(Data.EvaluatedData.Attribute == GetRegenerationAttribute())
	// {
	// 	const float LocalRegenerationDone = GetRegeneration();
	//
	// 	SetRegeneration(0.0f);
	// 	
	// 	if(LocalRegenerationDone > 0.0f)
	// 	{
	// 		const float NewMana = GetCurrentMana() + LocalRegenerationDone;
	// 		SetCurrentMana(FMath::Clamp(NewMana, 0.0f, GetMaximumMana()));
	//
	// 		if(ACharacterBase* AvatarCharacter = Cast<ACharacterBase>(Data.Target.GetAvatarActor()))
	// 		{
	// 			AvatarCharacter->OnManaRegen();
	// 		}
	// 	}
	// }
	// else if(Data.EvaluatedData.Attribute == GetCurrentManaAttribute())
	// {
	// 	SetCurrentMana(FMath::Clamp(GetCurrentMana(), 0.0f, GetMaximumMana()));
	// }
	// else if(Data.EvaluatedData.Attribute == GetManaRegenerationAttribute())
	// {
	// 	SetManaRegeneration(FMath::Clamp(GetManaRegeneration(), 0.0f, GetMaximumMana()));
	// }
#pragma endregion
}


void UManaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Water
	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, CurrentWaterMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, MaximumWaterMana, COND_None, REPNOTIFY_Always);

	//Earth
	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, CurrentEarthMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, MaximumEarthMana, COND_None, REPNOTIFY_Always);

	//Fire
	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, CurrentFireMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, MaximumFireMana, COND_None, REPNOTIFY_Always);

	//Air
	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, CurrentAirMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, MaximumAirMana, COND_None, REPNOTIFY_Always);
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
		const float NewDelta = (CurrentMaxValue > 0.f)
			                       ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue
			                       : NewMaxValue;

		AbilitySystemComponent->
			ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

//Water
void UManaAttributeSet::OnRep_CurrentWaterMana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, CurrentWaterMana, OldMana);
}

void UManaAttributeSet::OnRep_MaximumWaterMana(const FGameplayAttributeData& OldMaxWaterMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, MaximumWaterMana, OldMaxWaterMana);
}

//Earth
void UManaAttributeSet::OnRep_CurrentEarthMana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, CurrentEarthMana, OldMana);
}

void UManaAttributeSet::OnRep_MaximumEarthMana(const FGameplayAttributeData& OldMaxEarthMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, MaximumEarthMana, OldMaxEarthMana);
}

//Fire
void UManaAttributeSet::OnRep_CurrentFireMana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, CurrentFireMana, OldMana);
}

void UManaAttributeSet::OnRep_MaximumFireMana(const FGameplayAttributeData& OldMaxFireMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, MaximumFireMana, OldMaxFireMana);
}

//Air
void UManaAttributeSet::OnRep_CurrentAirMana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, CurrentAirMana, OldMana);
}

void UManaAttributeSet::OnRep_MaximumAirMana(const FGameplayAttributeData& OldMaxAirMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, MaximumAirMana, OldMaxAirMana);
}
