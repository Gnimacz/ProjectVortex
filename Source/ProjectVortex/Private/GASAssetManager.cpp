// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVortex/Public/GASAssetManager.h"

#include "AbilitySystemGlobals.h"

void UGASAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Warning, TEXT("UGASAssetManager::StartInitialLoading()"));
}
