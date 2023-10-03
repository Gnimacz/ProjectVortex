// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVortex/Public/GameplayAbilities/CustomGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "VREditorMode.h"
#include "ProjectVortex/Public/FunctionLibrary/AbilitySystemFunctionLibrary.h"

UCustomGameplayAbility::UCustomGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

float UCustomGameplayAbility::GetModifiedAbilityStrength()
{
	float BaseStrength = BaseAbilityStrength.GetValueAtLevel(GetAbilityLevel());

	if(const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo())
	{
		for(const FAbilityModifierStruct& Modifier : AbilityModifiers)
		{
			if (const float AttributeValue = UAbilitySystemFunctionLibrary::GetAttributeValueFromAbilitySystem(AbilitySystemComponent, Modifier.BackingAttribute, Modifier.AttributeSearchType) != -1.0f)
			{
				BaseStrength += AttributeValue * Modifier.AttributeModifier;
			}
		}
	}
	return BaseStrength;
}

void UCustomGameplayAbility::K2_EndAbility()
{
	Super::K2_EndAbility();
}

void UCustomGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if(ActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
