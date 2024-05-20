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
		FMyAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(pair.Key);
		Info.AttributeValue = pair.Value.GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

void UMyAttributeMenuWidgetController::BindCallbacksToDependecies()
{
	UMyAttributeSet* AS = Cast<UMyAttributeSet>(AttributeSet);

	for (const auto& pair : AS->TagToAttributes) 
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(pair.Value).AddLambda(
			[this, pair, AS](const FOnAttributeChangeData& Data)
			{
				FMyAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(pair.Key);
				Info.AttributeValue = pair.Value.GetNumericValue(AS);
				AttributeInfoDelegate.Broadcast(Info);
			}
		);
	}

}
