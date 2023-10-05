// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVortex/Public/GameplayAbilityComponent/CustomAbilitySystemComponent.h"

#include "ProjectVortex/Public/GameplayAbilities/CustomGameplayAbility.h"

struct FPredictionKey;

UCustomAbilitySystemComponent::UCustomAbilitySystemComponent()
{
}


FGameplayAbilitySpec* UCustomAbilitySystemComponent::HasAbility(TSubclassOf<UGameplayAbility> AbilityToCheck)
{
	//loop through all the granted abilities and see if the ability is 
	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;
	this->GetAllAbilities(GrantedAbilities);

	FGameplayAbilitySpec* FoundAbilitySpec = nullptr;

	for(const FGameplayAbilitySpecHandle handle : GrantedAbilities)
	{
		if(this->FindAbilitySpecFromHandle(handle)->Ability == AbilityToCheck->GetDefaultObject<UCustomGameplayAbility>())
		{
			FoundAbilitySpec = this->FindAbilitySpecFromHandle(handle);
		}
	}

	return FoundAbilitySpec;
	
}

bool UCustomAbilitySystemComponent::HasAbilityClass(TSubclassOf<UGameplayAbility> AbilityToCheck,
                                                    FGameplayAbilitySpecHandle& FoundAbilitySpecHandle)
{
	for (FGameplayAbilitySpec Spec : this->GetActivatableAbilities())
	{
		if (Spec.Ability == AbilityToCheck->GetDefaultObject<UCustomGameplayAbility>())
		{
			FoundAbilitySpecHandle = Spec.Handle;
			return true;
		}
	}
	return false;
}

void UCustomAbilitySystemComponent::ActivateAbilityByClass(bool& WasReleased,
                                                           TEnumAsByte<EBranchEnum> Activation,
                                                           TSubclassOf<UGameplayAbility> AbilityToActivate,
                                                           bool bAllowRemoteActivation)
{
	const FGameplayAbilitySpec* FoundAbilitySpec = HasAbility(AbilityToActivate);
	
	if(FoundAbilitySpec == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Ability found! Please make sure your ability is granted!"));
		return;
	}

	if (Activation == EBranchEnum::Pressed)
	{
		TryActivateAbility(FoundAbilitySpec->Handle, bAllowRemoteActivation);
		UE_LOG(LogTemp, Warning, TEXT("Pressed"));
		WasReleased = false;
	}
	else if (Activation == EBranchEnum::Released)
	{
		if (GetOwner()->GetLocalRole() == ROLE_Authority)
		{
			ServerEndAbility(FoundAbilitySpec->Handle, FoundAbilitySpec->ActivationInfo, FPredictionKey());
			ClientEndAbility(FoundAbilitySpec->Handle, FoundAbilitySpec->ActivationInfo);
			UE_LOG(LogTemp, Warning, TEXT("AUTHORITATIVE Released"));
		}
		else if (GetOwner()->GetLocalRole() != ROLE_Authority)
		{
			ClientEndAbility(FoundAbilitySpec->Handle, FoundAbilitySpec->ActivationInfo);
			UE_LOG(LogTemp, Warning, TEXT("NOT AUTHORITATIVE Released"));
		}
		CancelAbilityHandle(FoundAbilitySpec->Handle);

		UE_LOG(LogTemp, Warning, TEXT("Released"));
		WasReleased = true;
	}
}

int UCustomAbilitySystemComponent::UpgradeAbility(TSubclassOf<UGameplayAbility> AbilityToUpgrade, int Level,
	FGameplayAbilitySpecHandle& UpgradedAbilityHandle)
{
	FGameplayAbilitySpec* FoundAbilitySpec = HasAbility(AbilityToUpgrade);
	if(FoundAbilitySpec == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Ability found! Please make sure your ability is granted!"));
		return -1;
	}
	FoundAbilitySpec->Level = Level;
	return Level;
}
