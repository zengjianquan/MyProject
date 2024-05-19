// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetManager.h"
#include "MyGameplayTags.h"

UMyAssetManager& UMyAssetManager::Get()
{
	check(GEngine);
	return *Cast<UMyAssetManager>(GEngine->AssetManager);
}

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FMyGameplayTags::InitalizeNativeGameplayTags();
}
