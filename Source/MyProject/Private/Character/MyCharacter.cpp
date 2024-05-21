// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyCharacter.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AMyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AMyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

int32 AMyCharacter::GetPlayerLevel()
{
	return int32();
}

void AMyCharacter::InitAbilityActorInfo()
{
}

void AMyCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle =
		GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, 1.0, ContextHandle);;
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AMyCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.0f);
}

void AMyCharacter::AddCharacterAbilities()
{
	UMyAbilitySystemComponent* MyASC = CastChecked<UMyAbilitySystemComponent>(AbilitySystemComponent);

	//判断是否为服务端(权威端)
	if (!HasAuthority())
		return;

	MyASC->AddCharacterAbilities(StartupAbilities);
}
