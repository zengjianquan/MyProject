// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SplineComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

#include "MyGameplayTags.h"
#include "Input/MyEnhancedInputComponent.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"

AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(Context);

	//设置 subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	//只有当前Game instance 的 playercontroller 才是 LocalPlayer
	//例: listen server 中会有多个playercontroller, 但只有自身的 game instance 才是 local player
	//在 client 中会有 playercontroller 从服务端复制过来, 并且local player 为自身
	if (Subsystem) {
		Subsystem->AddMappingContext(Context, 0);
	}

	//设置 cursor 光标信息
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//
	UMyEnhancedInputComponent* MyEnhanceInputComponent = CastChecked<UMyEnhancedInputComponent>(InputComponent);
	MyEnhanceInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);

	MyEnhanceInputComponent->BindAbilityActions(InputConfig, this, 
		&AMyPlayerController::AbilityInputTagPressed, 
		&AMyPlayerController::AbilityInputTagReleased, 
		&AMyPlayerController::AbilityInputTagHeld);
}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRun();
}

void AMyPlayerController::CursorTrace()
{	
	LastActor = ThisActor;
	if (!GetHitResultUnderCursor(ECC_Visibility, false, CursorHit))
		ThisActor = nullptr;

	else
		ThisActor = Cast<IMyAIInterface>(CursorHit.GetActor());
}

void AMyPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}

}

void AMyPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FMyGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AMyPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FMyGameplayTags::Get().InputTag_LMB))
	{
		if (GetMyASC())
			GetMyASC()->AbilityInputTagReleased(InputTag);

		return;
	}

	if (bTargeting)
	{
		if (GetMyASC())
			GetMyASC()->AbilityInputTagReleased(InputTag);
	}
	else 
	{
		APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (UNavigationPath* NavPath =
				UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();

				for (const FVector& Point : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), Point, 8.f, 8, FColor::Green, false, 5.f);
				}
				CachedDestination = NavPath->PathPoints.Last();
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AMyPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FMyGameplayTags::Get().InputTag_LMB))
	{
		if (GetMyASC())
			GetMyASC()->AbilityInputTagHeld(InputTag);

		return;
	}

	if (bTargeting)
	{
		if (GetMyASC())
			GetMyASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		if (CursorHit.bBlockingHit)
			CachedDestination = CursorHit.ImpactPoint;

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UMyAbilitySystemComponent* AMyPlayerController::GetMyASC()
{
	if (MyAbilitySystemComponent == nullptr)
	{
		MyAbilitySystemComponent = Cast<UMyAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}

	return MyAbilitySystemComponent;
}

void AMyPlayerController::AutoRun()
{
	if (!bAutoRunning) return;

	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(
			ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(
			LocationOnSpline, ESplineCoordinateSpace::World);

		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}
