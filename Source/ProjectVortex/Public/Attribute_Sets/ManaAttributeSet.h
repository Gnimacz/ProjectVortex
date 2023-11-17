// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Characters/CharacterBase.h"
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
	
	//Water
	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_CurrentWaterMana)
	FGameplayAttributeData CurrentWaterMana;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, CurrentWaterMana);

	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_MaximumWaterMana)
	FGameplayAttributeData MaximumWaterMana;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, MaximumWaterMana);
	
	//Earth
	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_CurrentEarthMana)
	FGameplayAttributeData CurrentEarthMana;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, CurrentEarthMana);
	
	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_MaximumEarthMana)
	FGameplayAttributeData MaximumEarthMana;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, MaximumEarthMana);
	
	//Fire
	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_CurrentFireMana)
	FGameplayAttributeData CurrentFireMana;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, CurrentFireMana);
	
	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_MaximumFireMana)
	FGameplayAttributeData MaximumFireMana;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, MaximumFireMana);
	
	//Air
	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_CurrentAirMana)
	FGameplayAttributeData CurrentAirMana;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, CurrentAirMana);
	
	UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_MaximumAirMana)
	FGameplayAttributeData MaximumAirMana;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, MaximumAirMana);
	
#pragma region Not used
	// UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", ReplicatedUsing = OnRep_Regeneration)
	// FGameplayAttributeData ManaRegeneration;
	// ATTRIBUTE_ACCESSORS(UManaAttributeSet, ManaRegeneration);
	//
	// UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", meta = (HideFromLevelInfos))
	// FGameplayAttributeData Regeneration;
	// ATTRIBUTE_ACCESSORS(UManaAttributeSet, Regeneration);
	//
	// UPROPERTY(Blueprintreadonly, Category = "Mana Attribute Set", meta = (HideFromLevelInfos), ReplicatedUsing = OnRep_Drain)
	// FGameplayAttributeData ManaDrain;
	// ATTRIBUTE_ACCESSORS(UManaAttributeSet, ManaDrain);
#pragma endregion
	
protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	                                 const FGameplayAttributeData& MaxAttribute,
	                                 float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	//Water
	UFUNCTION()
	virtual void OnRep_CurrentWaterMana(const FGameplayAttributeData& OldMana);

	UFUNCTION()
	virtual void OnRep_MaximumWaterMana(const FGameplayAttributeData& OldMaxMana);

	//Earth
	UFUNCTION()
	virtual void OnRep_CurrentEarthMana(const FGameplayAttributeData& OldMana);

	UFUNCTION()
	virtual void OnRep_MaximumEarthMana(const FGameplayAttributeData& OldMaxMana);

	//Fire
	UFUNCTION()
	virtual void OnRep_CurrentFireMana(const FGameplayAttributeData& OldMana);
	
	UFUNCTION()
	virtual void OnRep_MaximumFireMana(const FGameplayAttributeData& OldMaxMana);

	//Air
	UFUNCTION()
	virtual void OnRep_CurrentAirMana(const FGameplayAttributeData& OldMana);
	
	UFUNCTION()
	virtual void OnRep_MaximumAirMana(const FGameplayAttributeData& OldMaxMana);
};
