// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MyEffectActor.h"

#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "AbilitySystem/MyAttributeSet.h"

// Sets default values
AMyEffectActor::AMyEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMyEffectActor::BeginPlay()
{
	Super::BeginPlay();

	//AddDynamic
	//当 sphere component 被 overlap 时触发 EffectActor 的 OnOverlap
	Sphere->OnComponentBeginOverlap.__Internal_AddDynamic(this, &ThisClass::OnOverlap, TEXT("OnOverlap"));
	Sphere->OnComponentEndOverlap.__Internal_AddDynamic(this, &ThisClass::EndOverlap, TEXT("EndOverlap"));
}

void AMyEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComponent, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: 使用 Gameplay Effect 来改变 Attribute, 现在使用 const_cast
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor)) {
		const UMyAttributeSet* MyAttributeSet = Cast<UMyAttributeSet>(
			ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UMyAttributeSet::StaticClass()));

		UMyAttributeSet* MyAttributeSet_ = const_cast<UMyAttributeSet*>(MyAttributeSet);
		MyAttributeSet_->SetHealth(MyAttributeSet->GetHealth() + 25.f);
		MyAttributeSet_->SetMana(MyAttributeSet->GetMana() - 25.f);
		Destroy();
	}
}

void AMyEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
}

