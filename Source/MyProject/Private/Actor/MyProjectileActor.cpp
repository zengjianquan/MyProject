// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MyProjectileActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AMyProjectileActor::AMyProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	//raycasts, sweeps, and overlaps
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AMyProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);

	Sphere->OnComponentBeginOverlap.__Internal_AddDynamic(this, &AMyProjectileActor::OnSphereOverlap, TEXT("OnSphereOverlap"));

	//LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}

void AMyProjectileActor::Destroyed()
{
	//当客户端没有执行 Overlap 时
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		//LoopingSoundComponent->Stop();
	}

	Super::Destroyed();
}

void AMyProjectileActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (TargetASC &&
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()) == TargetASC)
		return;

	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	//LoopingSoundComponent->Stop();

	if (HasAuthority())
	{
		if (TargetASC) 
		{
			TargetASC->ApplyGameplayEffectSpecToSelf((*DamageEffectSpecHandle.Data.Get()));
		}

		Destroy();
	}
	else //避免服务端先 Destroy, 客户端没有进行 Overlap, 导致没有 Impact 效果
	{
		bHit = true;	//使用一个 bool 值, 判断是否 Overlap
	}
}

