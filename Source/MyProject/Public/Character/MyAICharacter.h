// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacter.h"
#include "MyAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyAICharacter : public AMyCharacter
{
	GENERATED_BODY()
public:
	AMyAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
