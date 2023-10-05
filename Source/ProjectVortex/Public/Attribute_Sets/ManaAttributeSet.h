// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ManaAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROJECTVORTEX_API UManaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UManaAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_CurrentMana)
	FGameplayAttributeData CurrentMana;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, CurrentMana);

	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_MaximumMana)
	FGameplayAttributeData MaximumMana;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, MaximumMana);

	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_Regeneration)
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, ManaRegeneration);

	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Regeneration;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, Regeneration);

	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData ManaDrain;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, ManaDrain);

protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	                                 const FGameplayAttributeData& MaxAttribute,
	                                 float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	UFUNCTION()
	virtual void OnRep_CurrentMana(const FGameplayAttributeData& OldMana);

	UFUNCTION()
	virtual void OnRep_MaximumMana(const FGameplayAttributeData& OldMaxMana);

	UFUNCTION()
	virtual void OnRep_Regeneration(const FGameplayAttributeData& OldRegeneration);
};
