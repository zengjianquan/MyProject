// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
private:
	FGameplayEffectAttributeCaptureDefinition VigorDef;

public:
	UMMC_MaxHealth();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
