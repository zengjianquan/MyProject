// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacter.h"

#include "Interaction/MyAIInterface.h"

#include "MyAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyAICharacter : public AMyCharacter, public IMyAIInterface
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

public:
	AMyAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//~ Begin IMyCombatInterface
	virtual int32 GetPlayerLevel() override;
	//~ End IMyCombatInterface

private:
	virtual void InitAbilityActorInfo() override;

};
