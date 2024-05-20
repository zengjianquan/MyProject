// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/MyWidgetController.h"

#include "AbilitySystem/Data/MyAttributeInfoDataAsset.h"

#include "MyAttributeMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FMyAttributeInfo&, Info);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UMyAttributeMenuWidgetController : public UMyWidgetController
{
	GENERATED_BODY()
	
public:
	//~ Begin UMyWidgetController
	virtual void BroadcastInitalValues();
	virtual void BindCallbacksToDependecies();
	//~ End UMyWidgetController

protected:
	void BroadcastAttributeInfoDelegate(const FGameplayTag& Tag, const FGameplayAttribute& Attrbute) const;

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMyAttributeInfoDataAsset> AttributeInfo;
};
