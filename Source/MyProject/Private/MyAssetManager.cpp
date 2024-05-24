// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetManager.h"
#include "MyGameplayTags.h"
#include "AbilitySystemGlobals.h"

UMyAssetManager& UMyAssetManager::Get()
{
	check(GEngine);
	return *Cast<UMyAssetManager>(GEngine->AssetManager);
}

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FMyGameplayTags::InitalizeNativeGameplayTags();

	//使用 Target 的必要条件
	UAbilitySystemGlobals::Get().InitGlobalData();
}
