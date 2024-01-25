// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MyGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SaveGame_BestTime.h"

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

	static ConstructorHelpers::FClassFinder<USaveGame_BestTime> BestTimeClassRef(TEXT("/Script/MyProject5.SaveGame_BestTime"));
	if (BestTimeClassRef.Class)
	{
		BestTimeClass = BestTimeClassRef.Class;
	}
}

void AMyGameMode::BeginPlay()
{
	// Add time per second
	GetWorld()->GetTimerManager().SetTimer(TimeHandle, FTimerDelegate::CreateLambda(
		[&]() {
			SurvivalTime++;
		}),1.0f, true, 1.0f);

	LoadGame();
}

void AMyGameMode::GameClear()
{
	GetWorldTimerManager().ClearTimer(TimeHandle);
	SaveGame();
}

void AMyGameMode::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist(BestTimeSlotName, BestTimeSlotIdx))
	{
		USaveGame_BestTime* BT = Cast<USaveGame_BestTime>(UGameplayStatics::LoadGameFromSlot(BestTimeSlotName, BestTimeSlotIdx));
		BestTime = BT->GetBestSeconds();
	}
	else
	{
		BestTime = 99999;
	}
}

void AMyGameMode::SaveGame()
{
	if (SurvivalTime >= BestTime)
	{
		return;
	}
	BestTime = SurvivalTime;
	IsBest = true;

	USaveGame_BestTime* BT = Cast<USaveGame_BestTime>(UGameplayStatics::CreateSaveGameObject(BestTimeClass));
	BT->SetBestSeconds(BestTime);
	UGameplayStatics::SaveGameToSlot(BT, BestTimeSlotName, BestTimeSlotIdx);
}
