// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MyHUD.h"

#include "UI/Widget/MyUserWidget.h"
#include "UI/WidgetController/MyOverlayWidgetController.h"

TObjectPtr<class UMyOverlayWidgetController> AMyHUD::GetOverlayWidgetController(const FWdigetControllerParams& Params)
{
	if (OverlayWidgetController == nullptr) {
		OverlayWidgetController = NewObject<UMyOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(Params);
		OverlayWidgetController->BindCallbacksToDependecies();
	}
	return OverlayWidgetController;
}

void AMyHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class Uninitalized"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class Uninitalized"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UMyUserWidget>(Widget);

	const FWdigetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UMyOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitalValues();

	Widget->AddToViewport();
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	
}
