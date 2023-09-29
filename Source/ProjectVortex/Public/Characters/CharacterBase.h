// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract, NotBlueprintable)
class PROJECTVORTEX_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UCustomGameplayAbility>> DefaultAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayEffect>> DefaultEffects;

	void OnDeath();
	void OnDamage();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Character Base")
	void On_Death();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character Base")
	void On_Damage();
	
protected:

	TWeakObjectPtr<class UCustomAbilitySystemComponent> AbilitySystemComponent;


	//ADD EXTRA ATTRIBUTE SETS HERE
	UPROPERTY(BlueprintReadOnly, Category = "Character Base")
	TWeakObjectPtr<class UHealthAttributeSet> HealthAttributes;

	UPROPERTY(BlueprintReadOnly, Category = "Character Base")
	TWeakObjectPtr<class UMovementSpeedAttributeSet> MovementSpeedAttributes;

	void GiveDefaultAbilities();

	void ApplyDefaultEffects();

};
