// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/MyAttributeMenuWidgetController.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "MyGameplayTags.h"

void UMyAttributeMenuWidgetController::BroadcastInitalValues()
{
	UMyAttributeSet* AS = Cast<UMyAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (const auto& pair : AS->TagToAttributes) 
	{
		BroadcastAttributeInfoDelegate(pair.Key, pair.Value);
	}
}

void UMyAttributeMenuWidgetController::BindCallbacksToDependecies()
{
	UMyAttributeSet* AS = Cast<UMyAttributeSet>(AttributeSet);

	for (const auto& pair : AS->TagToAttributes) 
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(pair.Value).AddLambda(
			[this, pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfoDelegate(pair.Key, pair.Value);
			}
		);
	}

}

void UMyAttributeMenuWidgetController::BroadcastAttributeInfoDelegate(const FGameplayTag& Tag, 
	const FGameplayAttribute& Attrbute) const
{
	FMyAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Tag);
	Info.AttributeValue = Attrbute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
