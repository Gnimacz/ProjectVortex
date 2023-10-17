// Fill out your copyright notice in the Description page of Project Settings.


#include "CancelOut.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemLog.h"
#include "Algo/Find.h"
#include "Misc/DataValidation.h"

#define LOCTEXT_NAMESPACE "TargetTagRequirementsGameplayEffectComponent"

UCancelOut::UCancelOut()
{
#if WITH_EDITORONLY_DATA
	EditorFriendlyName = TEXT("Tags that Cancel Out This Gameplay Effect(While it's applied)");
#endif // WITH_EDITORONLY_DATA
}

bool UCancelOut::CanGameplayEffectApply(const FActiveGameplayEffectsContainer& ActiveGEContainer,
                                        const FGameplayEffectSpec& GESpec) const
{
	FGameplayTagContainer Tags;
	ActiveGEContainer.Owner->GetOwnedGameplayTags(Tags);

	

	return true;
}

// UCancelOut lives on an asset.  This doesn't get instanced at runtime, so this is NOT A UNIQUE INSTANCE (it is a shared instance for any GEContainer/ActiveGE that wants to use it).
bool UCancelOut::OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& GEContainer,
                                             FActiveGameplayEffect& ActiveGE) const
{
	UAbilitySystemComponent* ASC = GEContainer.Owner;
	if (!ensure(ASC))
	{
		return false;
	}

	FActiveGameplayEffectHandle ActiveGEHandle = ActiveGE.Handle;
	if (FActiveGameplayEffectEvents* EventSet = ASC->GetActiveEffectEventSet(ActiveGEHandle))
	{
		
		// Quick method of appending a TArray to another TArray with no duplicates.
		auto AppendUnique = [](TArray<FGameplayTag>& Destination, const TArray<FGameplayTag>& Source)
		{
			// Make sure the array won't allocate during the loop
			if (Destination.GetSlack() < Source.Num())
			{
				Destination.Reserve(Destination.Num() + Source.Num());
			}
			const TConstArrayView<FGameplayTag> PreModifiedDestinationView{Destination.GetData(), Destination.Num()};

			for (const FGameplayTag& Tag : Source)
			{
				if (!Algo::Find(PreModifiedDestinationView, Tag))
				{
					Destination.Emplace(Tag);
				}
			}
		};

		// We should gather a list of tags to listen on events for
		TArray<FGameplayTag> GameplayTagsToBind;
		AppendUnique(GameplayTagsToBind, CancelTagRequirements.IgnoreTags.GetGameplayTagArray());
		AppendUnique(GameplayTagsToBind, CancelTagRequirements.RequireTags.GetGameplayTagArray());
		AppendUnique(GameplayTagsToBind, CancelTagRequirements.TagQuery.GetGameplayTagArray());

		// Add our tag requirements to the ASC's Callbacks map. This helps filter down the amount of callbacks we'll get due to tag changes
		// (rather than registering for the one callback whenever any tag changes).  We also need to keep track to remove those registered delegates in OnEffectRemoved.
		TArray<TTuple<FGameplayTag, FDelegateHandle>> AllBoundEvents;
		for (const FGameplayTag& Tag : GameplayTagsToBind)
		{
			FOnGameplayEffectTagCountChanged& OnTagEvent = ASC->RegisterGameplayTagEvent(
				Tag, EGameplayTagEventType::NewOrRemoved);
			FDelegateHandle Handle = OnTagEvent.AddUObject(this, &UCancelOut::OnTagChanged, ActiveGEHandle);
			AllBoundEvents.Emplace(Tag, Handle);
		}

		// Now when this Effect is removed, we should remove all of our registered callbacks.
		EventSet->OnEffectRemoved.AddUObject(this, &UCancelOut::OnGameplayEffectRemoved, ASC, MoveTemp(AllBoundEvents));
	}
	else
	{
		UE_LOG(LogGameplayEffects, Error,
		       TEXT(
			       "UCancelOut::OnGameplayEffectAdded called with ActiveGE: %s which had an invalid FActiveGameplayEffectHandle."
		       ), *ActiveGE.GetDebugString());
	}

	FGameplayTagContainer TagContainer;
	ASC->GetOwnedGameplayTags(TagContainer);
	if(!CancelTagRequirements.IsEmpty() && CancelTagRequirements.RequirementsMet(TagContainer) == true)
	{
		GEContainer.Owner->RemoveActiveGameplayEffect(ActiveGEHandle);
		GEContainer.Owner->RemoveActiveEffectsWithTags(CancelTagRequirements.RequireTags);
	}

	return true;
}

void UCancelOut::OnGameplayEffectRemoved(const FGameplayEffectRemovalInfo& GERemovalInfo, UAbilitySystemComponent* ASC,
                                         TArray<TTuple<FGameplayTag, FDelegateHandle>> AllBoundEvents) const
{
	for (TTuple<FGameplayTag, FDelegateHandle>& Pair : AllBoundEvents)
	{
		const bool bSuccess = ASC->
			UnregisterGameplayTagEvent(Pair.Value, Pair.Key, EGameplayTagEventType::NewOrRemoved);
		UE_CLOG(!bSuccess, LogGameplayEffects, Error,
		        TEXT("%s tried to unregister GameplayTagEvent '%s' on GameplayEffect '%s' but failed."), *GetName(),
		        *Pair.Key.ToString(), *GetNameSafe(GetOwner()));
	}
}

void UCancelOut::OnTagChanged(const FGameplayTag GameplayTag, int32 NewCount,
                              FActiveGameplayEffectHandle ActiveGEHandle) const
{
	// Note: This function can remove us (RemoveActiveGameplayEffect eventually calling OnGameplayEffectRemoved),
	// but we could be in the middle of a stack of OnTagChanged callbacks, wo we could get a stale OnTagChanged.
	UAbilitySystemComponent* Owner = ActiveGEHandle.GetOwningAbilitySystemComponent();
	if (!Owner)
	{
		return;
	}
	const FActiveGameplayEffect* ActiveGE = Owner->GetActiveGameplayEffect(ActiveGEHandle);
	if (ensure(ActiveGE) && !ActiveGE->IsPendingRemove)
	{
		FGameplayTagContainer OwnedTags;
		Owner->GetOwnedGameplayTags(OwnedTags);
		

		const bool bCancelRequirementsMet = !CancelTagRequirements.IsEmpty() && CancelTagRequirements.
			RequirementsMet(OwnedTags);
		if (bCancelRequirementsMet)
		{
			// This is slightly different functionality from pre-UE5.3, we're calling RemoveActiveGameplayEffect rather than InternalRemoveActiveGameplayEffect.
			// The result is we set the calculated magnitudes back to zero.  This also used to only run on the Server.
			Owner->RemoveActiveGameplayEffect(ActiveGEHandle);
			Owner->RemoveActiveEffectsWithTags(CancelTagRequirements.RequireTags);
		}

		
	}
}

#if WITH_EDITOR
/**
 * Validate incompatable configurations
 */
EDataValidationResult UCancelOut::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	// const bool bInstantEffect = (GetOwner()->DurationPolicy == EGameplayEffectDurationType::Instant);
	// if (bInstantEffect && !OngoingTagRequirements.IsEmpty())
	// {
	// 	Context.AddError(LOCTEXT("GEInstantAndOngoing", "GE is instant but has OngoingTagRequirements."));
	// 	Result = EDataValidationResult::Invalid;
	// }

	return Result;
}
#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
