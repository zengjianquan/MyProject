// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/MyInputConfigDataAsset.h"
#include "InputAction.h"

const UInputAction* UMyInputConfigDataAsset::FindAbilityInputActionForTag(const FGameplayTag& InputTag) const
{
	int32 Index = AbilityInputActions.IndexOfByPredicate(
		[InputTag](const FMyInputAction& MyInputAction) {
			return MyInputAction.InputTag.MatchesTagExact(InputTag) && MyInputAction.InputAction;
		});

	if (Index == INDEX_NONE)
		return nullptr;

	return AbilityInputActions[Index].InputAction;
}
