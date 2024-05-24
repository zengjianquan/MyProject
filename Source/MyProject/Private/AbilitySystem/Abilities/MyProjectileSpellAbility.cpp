// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MyProjectileSpellAbility.h"
#include "Actor/MyProjectileActor.h"
#include "Interaction/MyCombatInterface.h"

void UMyProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UMyProjectileSpellAbility::SpawnProjectile()
{

	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if (!bIsServer)
		return;

	IMyCombatInterface* CombatInterface = Cast<IMyCombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		AMyProjectileActor* Projectile = GetWorld()->SpawnActorDeferred<AMyProjectileActor>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);



		Projectile->FinishSpawning(SpawnTransform);
	}

}
