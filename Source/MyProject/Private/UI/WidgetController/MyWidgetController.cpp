// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/MyWidgetController.h"

void UMyWidgetController::SetWidgetControllerParams(const FWdigetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}

void UMyWidgetController::BroadcastInitalValues()
{
}

void UMyWidgetController::BindCallbacksToDependecies()
{
}
