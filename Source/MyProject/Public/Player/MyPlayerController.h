// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"

#include "Interaction/MyAIInterface.h"

#include "MyPlayerController.generated.h"

class UMyAbilitySystemComponent;
class USplineComponent;

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> Context;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	IMyAIInterface* ThisActor;
	IMyAIInterface* LastActor;
	FHitResult CursorHit;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UMyInputConfigDataAsset> InputConfig;

	TObjectPtr<UMyAbilitySystemComponent> MyAbilitySystemComponent;

	FVector CachedDestination = FVector::Zero();
	float FollowTime = 0.0f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	//自动寻路接近的距离
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

public:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public:
	virtual void PlayerTick(float DeltaTime) override;

private:
	void CursorTrace();

	void Move(const struct FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UMyAbilitySystemComponent* GetMyASC();

	void AutoRun();
};
