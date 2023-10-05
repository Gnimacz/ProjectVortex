// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVortex/Public/Characters/CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "ProjectVortex/Public/GameplayAbilities/CustomGameplayAbility.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "ProjectVortex/Public/GameplayAbilityComponent/CustomAbilitySystemComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void ACharacterBase::OnDeath()
{
	On_Death();
}

void ACharacterBase::OnDamage()
{
	On_Damage();
}

void ACharacterBase::OnHeal()
{
	On_Heal();
}

void ACharacterBase::OnManaRegen()
{
	On_Mana_Regeneration();
}

void ACharacterBase::OnManaEmpty()
{
	On_Mana_Depleted();
}

void ACharacterBase::OnManaDrain()
{
	On_Mana_Drain();
}

void ACharacterBase::GiveDefaultAbilities()
{
	if(AbilitySystemComponent->bDefaultabilitiesGiven || GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	for(TSubclassOf<UCustomGameplayAbility>& Ability : DefaultAbilities)
	{
		if(IsValid(Ability))
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->InputBinding), this));
		}
	}

	AbilitySystemComponent->bDefaultabilitiesGiven = true;
}

void ACharacterBase::ApplyDefaultEffects()
{
	if(AbilitySystemComponent->bDefaultEffectsApplied || GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	for(TSubclassOf<UGameplayEffect>& Effect : DefaultEffects)
	{
		if(IsValid(Effect))
		{
			FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
			EffectContextHandle.AddSourceObject(this);

			FGameplayEffectSpecHandle GameplayEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContextHandle);

			if(GameplayEffectSpecHandle.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(), AbilitySystemComponent.Get());
			}
		}
	}
}

