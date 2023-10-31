// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, float, Health);

UCLASS(Abstract, NotBlueprintable)
class PROJECTVORTEX_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintAssignable, Category = "GAS")
	FOnHealthChangedDelegate OnHealthChangedDelegate;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UCustomGameplayAbility>> DefaultAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayEffect>> DefaultEffects;

	void OnDeath();
	void OnDamage();
	void OnHeal();
	void OnManaEmpty();
	void OnManaDrain();
	void OnManaRegen();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Character Base")
	void On_Death();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character Base")
	void On_Damage();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character Base")
	void On_Heal();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character Base")
	void On_Mana_Drain();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character Base")
	void On_Mana_Depleted();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character Base")
	void On_Mana_Regeneration();
	
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
