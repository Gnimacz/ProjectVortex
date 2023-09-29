// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "GASAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVORTEX_API UGASAssetManager : public UAssetManager
{
	GENERATED_BODY()

	virtual void StartInitialLoading() override;
};