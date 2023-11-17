// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVortex/Public/PlayerState/PlayerStateBase.h"

#include "ProjectVortex/Public/Attribute_Sets/HealthAttributeSet.h"
#include "ProjectVortex/Public/Attribute_Sets/MovementSpeedAttributeSet.h"
#include "ProjectVortex/Public/GameplayAbilityComponent/CustomAbilitySystemComponent.h"

APlayerStateBase::APlayerStateBase()
{
	NetUpdateFrequency = 60.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UCustomAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Mixed;

	//Create the Health Attribute Set sub-object.
	//If you want to add other attribute sets you can do so here by copying the line above and changing the class type.
	HealthAttributes = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("HealthAttributes"));
	
	MovementSpeedAttributes = CreateDefaultSubobject<UMovementSpeedAttributeSet>(TEXT("MovementSpeedAttributes"));
	
	ManaAttributes = CreateDefaultSubobject<UManaAttributeSet>(TEXT("ManaAttributes"));

	
}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
