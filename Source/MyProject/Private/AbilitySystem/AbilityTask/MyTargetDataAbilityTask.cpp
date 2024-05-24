// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/MyTargetDataAbilityTask.h"
#include "AbilitySystemComponent.h"

UMyTargetDataAbilityTask* UMyTargetDataAbilityTask::CreateTargetDataUnderCursor(UGameplayAbility* OwningAbility)
{
	UMyTargetDataAbilityTask* MyObj = NewAbilityTask<UMyTargetDataAbilityTask>(OwningAbility);
	return MyObj;
}

void UMyTargetDataAbilityTask::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredicationKey = GetActivationPredictionKey();
		AbilitySystemComponent->AbilityTargetDataSetDelegate(
			SpecHandle, ActivationPredicationKey).AddLambda(
				[this](const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
				{
					if (ShouldBroadcastAbilityTaskDelegates())
					{
						ValidData.Broadcast(DataHandle);
					}

					AbilitySystemComponent->ConsumeClientReplicatedTargetData(
						GetAbilitySpecHandle(), GetActivationPredictionKey());

				});

		const bool bCalledDelegate =
			AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredicationKey);

		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UMyTargetDataAbilityTask::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	FGameplayAbilityTargetData_SingleTargetHit* Data =
		new FGameplayAbilityTargetData_SingleTargetHit();

	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	PC->GetHitResultUnderCursor(ECC_Visibility, false, Data->HitResult);

	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);

	FGameplayTag ApplicationTag;

	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		ApplicationTag,
		AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
