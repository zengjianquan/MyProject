// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MyAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UMyAssetManager& Get();

protected:
	//~ Begin UAssetManager
	virtual void StartInitialLoading() override;
	//~ End UAssetManager
};
