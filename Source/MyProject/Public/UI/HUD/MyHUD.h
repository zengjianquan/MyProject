// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<class UMyUserWidget> OverlayWidget;

	TObjectPtr<class UMyOverlayWidgetController> GetOverlayWidgetController(const struct FWdigetControllerParams& Params);

	void InitOverlay(APlayerController* PC, APlayerState* PS, class UAbilitySystemComponent* ASC, class UAttributeSet* AS);

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMyUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<class UMyOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMyOverlayWidgetController> OverlayWidgetControllerClass;

protected:
	virtual void BeginPlay() override;
};
