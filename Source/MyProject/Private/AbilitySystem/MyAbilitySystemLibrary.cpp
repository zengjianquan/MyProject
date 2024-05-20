// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "UI/HUD/MyHUD.h"
#include "Player/MyPlayerState.h"

UMyOverlayWidgetController* UMyAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMyHUD* MyHUD = Cast<AMyHUD>(PC->GetHUD()))
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWdigetControllerParams WdigetControllerParams(PC, PS, ASC, AS);
			return MyHUD->GetOverlayWidgetController(WdigetControllerParams);
		}
	}

	return nullptr;
}

UMyAttributeMenuWidgetController* UMyAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMyHUD* MyHUD = Cast<AMyHUD>(PC->GetHUD()))
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWdigetControllerParams WdigetControllerParams(PC, PS, ASC, AS);
			return MyHUD->GetAttributeMenuWidgetController(WdigetControllerParams);
		}
	}

	return nullptr;
}
