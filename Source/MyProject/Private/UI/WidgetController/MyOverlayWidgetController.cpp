// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/MyOverlayWidgetController.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"

void UMyOverlayWidgetController::BroadcastInitalValues()
{
	UMyAttributeSet* MyAttributeSet = CastChecked<UMyAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(MyAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MyAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(MyAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(MyAttributeSet->GetMaxMana());
}

void UMyOverlayWidgetController::BindCallbacksToDependecies()
{
	UMyAttributeSet* MyAttributeSet = CastChecked<UMyAttributeSet>(AttributeSet);

	//通过 AttributeSet 获取 Attribute, 然后通过 ASC 添加该 Attribute 更改时的委托
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MyAttributeSet->GetHealthAttribute()
	).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MyAttributeSet->GetMaxHealthAttribute()
	).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MyAttributeSet->GetManaAttribute()
	).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MyAttributeSet->GetMaxManaAttribute()
	).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags) 
		{
			for (const auto& Tag : AssetTags) {
				FGameplayTag TagRequest = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(TagRequest)) 
				{
					FUIWidgetRow* Row = 
						MessageDataTable->FindRow<FUIWidgetRow>(Tag.GetTagName(), TEXT(""));

					MessageWidgetRowDelegate.Broadcast(*Row);
				}

			}
		}
	);
}
