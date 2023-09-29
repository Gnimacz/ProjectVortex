// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVortex/Public/Subsystem/AbilitySubsystem.h"

#include "AbilitySystemGlobals.h"

void UAbilitySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UAbilitySystemGlobals::Get().InitGlobalData();
}
