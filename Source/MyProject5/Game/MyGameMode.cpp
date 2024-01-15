// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MyGameMode.h"

AMyGameMode::AMyGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PawnRef(TEXT("/Script/MyProject5.PlayerCharacter_C"));
	if (PawnRef.Class)
	{
		DefaultPawnClass = PawnRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> ControllerRef(TEXT("/Script/MyProject5.MyPlayerController"));
	if (ControllerRef.Class)
	{
		PlayerControllerClass = ControllerRef.Class;
	}
}

void AMyGameMode::BeginPlay()
{
	// Add time per second
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda(
		[&]() {
			SurvivalTime++;
		}),1.0f, true, 1.0f);
}
