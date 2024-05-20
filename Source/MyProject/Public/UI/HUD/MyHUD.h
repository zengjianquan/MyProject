// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
class UMyOverlayWidgetController;
class UMyAttributeMenuWidgetController;
class UMyUserWidget;

UCLASS()
class MYPROJECT_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	TObjectPtr<UMyOverlayWidgetController> GetOverlayWidgetController(const struct FWdigetControllerParams& Params);

	TObjectPtr<UMyAttributeMenuWidgetController> GetAttributeMenuWidgetController(const struct FWdigetControllerParams& Params);

	void InitOverlay(APlayerController* PC, APlayerState* PS, class UAbilitySystemComponent* ASC, class UAttributeSet* AS);

private:
	UPROPERTY()
	TObjectPtr<UMyUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMyUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UMyOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMyOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UMyAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMyAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

protected:
	virtual void BeginPlay() override;
};
