// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS(Blueprintable)
class MYPROJECT_API AMyActor : public AActor
{

	GENERATED_BODY()
private:
	TSharedPtr<class FCTSceneViewExtension, ESPMode::ThreadSafe> CTSceneViewExtension;

public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
