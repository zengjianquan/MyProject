// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "Interaction/MyCombatInterface.h"

#include "MyCharacter.generated.h"

UCLASS(Abstract)
class MYPROJECT_API AMyCharacter : public ACharacter, public IAbilitySystemInterface, public IMyCombatInterface
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UGameplayEffect> DefaultSecondaryAttributes;

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAttributeSet* GetAttributeSet() const;

	// begin IMyCombatInterface
	virtual int32 GetPlayerLevel() override;
	// end IMyCombatInterface

protected:
	virtual void InitAbilityActorInfo();

	void ApplyEffectToSelf(TSubclassOf<class UGameplayEffect> GameplayEffectClass, float Level) const;

	void InitializeDefaultAttributes() const;
};
