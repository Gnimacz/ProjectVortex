// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/ActorComponent.h"
#include "AttributeSetHolderComponent.generated.h"


UCLASS( ClassGroup=(Custom), hidecategories=(Object,LOD,Lighting,Transform,Sockets,TextureStreaming), editinlinenew, meta=(BlueprintSpawnableComponent) )
class PROJECTVORTEX_API UAttributeSetHolderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeSetHolderComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attribute Sets")
	TArray<TSubclassOf<class UAttributeSet>> AttributeSets;

	virtual void BeginPlay() override;
};
