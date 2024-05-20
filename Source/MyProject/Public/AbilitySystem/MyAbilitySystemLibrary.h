// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "UI/WidgetController/MyOverlayWidgetController.h"
#include "UI/WidgetController/MyAttributeMenuWidgetController.h"

#include "MyAbilitySystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "My Ability System Library|Widget Controller")
	static UMyOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "My Ability System Library|Widget Controller")
	static UMyAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};
