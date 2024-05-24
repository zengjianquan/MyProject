// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MyTargetDataAbilityTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCursorTargetDataSignature, const FGameplayAbilityTargetDataHandle&, Data);

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyTargetDataAbilityTask : public UAbilityTask
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintAssignable)
	FCursorTargetDataSignature ValidData;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", 
		meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", 
			BlueprintInternalUseOnly = "TRUE", DisplayName = "TargetDataUnderCursor"))
	static UMyTargetDataAbilityTask* CreateTargetDataUnderCursor(UGameplayAbility* OwningAbility);

protected:
	virtual void Activate() override;

private:
	void SendMouseCursorData();
};
