// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyAICharacter.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"

AMyAICharacter::AMyAICharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
}

void AMyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AMyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

int32 AMyAICharacter::GetPlayerLevel()
{
	return Level;
}

void AMyAICharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}
