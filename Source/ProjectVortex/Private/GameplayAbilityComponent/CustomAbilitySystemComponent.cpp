// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVortex/Public/GameplayAbilityComponent/CustomAbilitySystemComponent.h"

#include "ProjectVortex/Public/GameplayAbilities/CustomGameplayAbility.h"

UCustomAbilitySystemComponent::UCustomAbilitySystemComponent()
{
	
}

bool UCustomAbilitySystemComponent::HasAbility(UAbilitySystemComponent* AbilitySystemComponent,
	FGameplayAbilitySpecHandle Ability)
{
	for (FGameplayAbilitySpec Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if (Spec.Handle == Ability)
		{
			return true;
		}
	}
	return false;
}

bool UCustomAbilitySystemComponent::HasAbilityClass(TSubclassOf<UGameplayAbility> InAbility, FGameplayAbilitySpecHandle &OutAbilitySpecHandle)
{
	for (FGameplayAbilitySpec Spec : this->GetActivatableAbilities())
	{
		if (Spec.Ability == InAbility->GetDefaultObject<UCustomGameplayAbility>())
		{
			OutAbilitySpecHandle = Spec.Handle;
			return true;
		}
	}
	return false;
}

// bool UCustomAbilitySystemComponent::HasAbility(UCustomAbilitySystemComponent* AbilitySystemComponent,
//                                                FGameplayAbilitySpecHandle* Ability)
// {
// 	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;
// 	for (FGameplayAbilitySpecHandle* Spec : AbilitySystemComponent->GetAllAbilities(GrantedAbilities))
// 	{
// 		if (Spec == Ability)
// 		{
// 			return true;
// 		}
// 	}
// 	return false;
// }


