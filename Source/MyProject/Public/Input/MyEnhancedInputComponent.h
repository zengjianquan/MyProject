// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"

#include "MyInputConfigDataAsset.h"

#include "MyEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<typename UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UMyInputConfigDataAsset* InputConfig,
		UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template<typename UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UMyEnhancedInputComponent::BindAbilityActions(const UMyInputConfigDataAsset* InputConfig,
	UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FMyInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}