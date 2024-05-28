// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyAICharacter.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"

#include "Components/WidgetComponent.h"

AMyAICharacter::AMyAICharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());
}

void AMyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	if (UMyUserWidget* MyUserWidget = Cast<UMyUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		MyUserWidget->SetWidgetController(this);
	}

	if (const UMyAttributeSet* AS = Cast<UMyAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AS->GetHealthAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data)
				{
					this->OnHealthChange.Broadcast(Data.NewValue);
				}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AS->GetMaxHealthAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data)
				{
					this->OnMaxHealthChange.Broadcast(Data.NewValue);
				}
		);

		OnHealthChange.Broadcast(AS->GetHealth());
		OnMaxHealthChange.Broadcast(AS->GetMaxHealth());
	}
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
