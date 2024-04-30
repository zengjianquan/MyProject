// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyControlCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Player/MyPlayerState.h"
#include "Player/MyPlayerController.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "UI/HUD/MyHUD.h"

AMyControlCharacter::AMyControlCharacter()
{
	auto CharacterMovementComp = GetCharacterMovement();
	CharacterMovementComp->bOrientRotationToMovement = true;	//使角色朝向加速方向
	CharacterMovementComp->RotationRate = FRotator(0.f, 400.f, 0.f);	//旋转速率
	CharacterMovementComp->bConstrainToPlane = true;	//限制在一个平面
	CharacterMovementComp->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AMyControlCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyControlCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyControlCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

void AMyControlCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void AMyControlCharacter::InitAbilityActorInfo()
{
	//初始化 actor ability info
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MyPlayerState, this);

	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttributeSet();

	//多人游戏中, 每个客户端只拥有自己角色的 PlayerController, 但是不止有一个角色
	//因此本函数会多次执行, 在 PlayerController 为空时, 不需要进行断言
	if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController())) {
		if (AMyHUD* MyHUD = Cast<AMyHUD>(PlayerController->GetHUD())) {
			MyHUD->InitOverlay(PlayerController, MyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	
}
