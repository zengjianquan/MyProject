// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/MyOverlayWidgetController.h"
#include "AbilitySystem/MyAttributeSet.h"

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
	).AddUObject(this, &UMyOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MyAttributeSet->GetMaxHealthAttribute()
	).AddUObject(this, &UMyOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MyAttributeSet->GetManaAttribute()
	).AddUObject(this, &UMyOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MyAttributeSet->GetMaxManaAttribute()
	).AddUObject(this, &UMyOverlayWidgetController::MaxManaChanged);
}

void UMyOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UMyOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UMyOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UMyOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
