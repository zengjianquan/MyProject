// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerState.h"

#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"

AMyPlayerState::AMyPlayerState()
{
	//同步频率
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	/*
	* +-------------------------------------------------------------——+
	* | Minimal | 只会将 Gameplay Cue 和 Gameplay Tags 复制到客户端	  | 单人游戏
	* +---------------------------------------------------------------+
	* | Mixed   | 在 Minimal 的基础上将 Gameplay Effect 拷贝到自己的客户端| 多人游戏 Player-Control
	* +---------------------------------------------------------------+
	* | Full	| 拷贝 Gamplay Effect 到所有客户端                      | 多人游戏 AI-Control
	* +---------------------------------------------------------------+
	*/
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AMyPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

