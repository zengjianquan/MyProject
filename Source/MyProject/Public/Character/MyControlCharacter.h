// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacter.h"
#include "MyControlCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyControlCharacter : public AMyCharacter
{
	GENERATED_BODY()
	
public:
	AMyControlCharacter();

	//~ Begin Actor Interface
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//~ End Actor Interface

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;
	//~ End APawn Interface.

private:
	void InitAbilityActorInfo();
};
