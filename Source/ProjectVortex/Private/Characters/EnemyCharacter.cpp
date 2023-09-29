// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVortex/Public/Characters/EnemyCharacter.h"

#include "ProjectVortex/Public/Attribute_Sets/HealthAttributeSet.h"
#include "ProjectVortex/Public/Attribute_Sets/MovementSpeedAttributeSet.h"
#include "ProjectVortex/Public/GameplayAbilityComponent/CustomAbilitySystemComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	Enemy_AbilitySystemComponent = CreateDefaultSubobject<UCustomAbilitySystemComponent>(TEXT("Enemy_AbilitySystemComponent"));
	Enemy_AbilitySystemComponent->SetIsReplicated(true);
	Enemy_AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Minimal;

	AbilitySystemComponent = Enemy_AbilitySystemComponent;

	//ATTRIBUTE SETS
	Enemy_HealthAttributes = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("Enemy_HealthAttributes"));
	HealthAttributes = Enemy_HealthAttributes;
	
	Enemy_MovementSpeedAttributeSet = CreateDefaultSubobject<UMovementSpeedAttributeSet>(TEXT("Enemy_MovementSpeedAttributeSet"));
	MovementSpeedAttributes = Enemy_MovementSpeedAttributeSet;
}

void AEnemyCharacter::BeginPlay()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	GiveDefaultAbilities();
	ApplyDefaultEffects();

	Super::BeginPlay();
}

