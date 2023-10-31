// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectVortex/Public/Attribute_Sets/HealthAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "ProjectVortex/Public/Characters/CharacterBase.h"
#include "Net/UnrealNetwork.h"

UHealthAttributeSet::UHealthAttributeSet()
{
	MaximumHealth = 0.0f;
	CurrentHealth = 0.0f;
	HealthRegeneration = 0.0f;
}

void UHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaximumHealthAttribute())
	{
		AdjustAttributeForMaxChange(CurrentHealth, MaximumHealth, NewValue, GetCurrentHealthAttribute());
	}
}

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float damageDone = GetDamage();

		SetDamage(0.0f);

		if(damageDone > 0.0f)
		{
			const float NewHealth = GetCurrentHealth() - damageDone;

			SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaximumHealth()));

			if(GetCurrentHealth() <= 0.0f)
			{
				if(ACharacterBase* AvatarCharacter = Cast<ACharacterBase>(Data.Target.GetAvatarActor()))
				{
					AvatarCharacter->OnDeath();
				}
			}
			else if(ACharacterBase* AvatarCharacter = Cast<ACharacterBase>(Data.Target.GetAvatarActor()))
			{
				AvatarCharacter->OnDamage();
				AvatarCharacter->OnHealthChangedDelegate.Broadcast(GetCurrentHealth());
			}
		}
	}
	else if(Data.EvaluatedData.Attribute == GetHealingAttribute())
	{
		const float LocalHealingDone = GetHealing();

		SetHealing(0.0f);
		
		if(LocalHealingDone > 0.0f)
		{
			const float NewHealth = GetCurrentHealth() + LocalHealingDone;
			SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaximumHealth()));
			if(ACharacterBase* AvatarCharacter = Cast<ACharacterBase>(Data.Target.GetAvatarActor()))
			{
				AvatarCharacter->OnHeal();
			}
		}
	}
	else if(Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaximumHealth()));
	}
	else if(Data.EvaluatedData.Attribute == GetHealthRegenerationAttribute())
	{
		SetHealthRegeneration(FMath::Clamp(GetHealthRegeneration(), 0.0f, GetMaximumHealth()));
	}
}

void UHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, MaximumHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
}

void UHealthAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
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

void UHealthAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, CurrentHealth, OldHealth);
}

void UHealthAttributeSet::OnRep_MaximumHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, MaximumHealth, OldMaxHealth);
}

void UHealthAttributeSet::OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, HealthRegeneration, OldRegeneration);
}
