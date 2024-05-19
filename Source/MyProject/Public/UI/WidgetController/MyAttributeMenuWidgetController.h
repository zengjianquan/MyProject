// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/MyWidgetController.h"
#include "MyAttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyAttributeMenuWidgetController : public UMyWidgetController
{
	GENERATED_BODY()
	
	//~ Begin UMyWidgetController
	virtual void BroadcastInitalValues();
	virtual void BindCallbacksToDependecies();
	//~ End UMyWidgetController
};
