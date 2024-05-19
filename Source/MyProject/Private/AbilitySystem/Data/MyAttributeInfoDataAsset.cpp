// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/MyAttributeInfoDataAsset.h"

FMyAttributeInfo UMyAttributeInfoDataAsset::FindAttributeInfoForTag(const FGameplayTag& AttributeTag) const
{
	int32 Index = AttributeInformation.IndexOfByPredicate(
		[AttributeTag](const FMyAttributeInfo& elem) {
		return elem.AttributeTag.MatchesTagExact(AttributeTag);
	});

	if (Index != INDEX_NONE)
	{
		return AttributeInformation[Index];
	}

	return FMyAttributeInfo();
}
