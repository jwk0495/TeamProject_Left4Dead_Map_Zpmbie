// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MyPlayerController.h"
#include "UI/HpBarWidget.h"
#include "UI/AmmoCountWidget.h"
#include "UI/CrosshairWidget.h"
#include "UI/ProcessUIWidget.h"
#include "UI/GameOverUIWidget.h"
#include "UI/NearbyItemWidget.h"
#include "UI/GameClearWidget.h"
#include "UI/PlayerHitWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Game/MyGameMode.h"
#include "UI/ClearAreaUIWidget.h"

AMyPlayerController::AMyPlayerController()
{
	static ConstructorHelpers::FClassFinder<UHpBarWidget> HpBarRef(TEXT("/Game/PKH/UI/WBP_HpBar.WBP_HpBar_C"));
	if (HpBarRef.Class)
	{
		HpBarClass = HpBarRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UAmmoCountWidget> AmmoCountRef(TEXT("/Game/PKH/UI/WBP_AmmoUI.WBP_AmmoUI_C"));
	if (AmmoCountRef.Class)
	{
		AmmoCountClass = AmmoCountRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UCrosshairWidget> CrossshairRef(TEXT("/Game/PKH/UI/WBP_CrosshairUI.WBP_CrosshairUI_C"));
	if (CrossshairRef.Class)
	{
		CrosshairClass = CrossshairRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UProcessUIWidget> ProcessUIRef(TEXT("/Game/PKH/UI/WBP_ProcessUI.WBP_ProcessUI_C"));
	if (ProcessUIRef.Class)
	{
		ProcessUIClass = ProcessUIRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UNearbyItemWidget> NearbyItemRef(TEXT("/Game/PKH/UI/WBP_NearbyItemUI.WBP_NearbyItemUI_C"));
	if (NearbyItemRef.Class)
	{
		NearbyItemUIClass = NearbyItemRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UPlayerHitWidget> HitEffectUIRef(TEXT("/Game/PKH/UI/WBP_PlayerHitEffect.WBP_PlayerHitEffect_C"));
	if (HitEffectUIRef.Class)
	{
		HitEffectUIClass = HitEffectUIRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UGameOverUIWidget> GameOverUIRef(TEXT("/Game/PKH/UI/WBP_GameOverUI.WBP_GameOverUI_C"));
	if (GameOverUIRef.Class)
	{
		GameOverUIClass = GameOverUIRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UGameClearWidget> GameClearUIRef(TEXT("/Game/PKH/UI/WBP_GameClearUI.WBP_GameClearUI_C"));
	if (GameClearUIRef.Class)
	{
		GameClearUIClass = GameClearUIRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UClearAreaUIWidget> ClearAreaUIRef(TEXT("/Game/PKH/UI/WBP_ClearAreaUI.WBP_ClearAreaUI_C"));
	if (ClearAreaUIRef.Class)
	{
		ClearAreaUIClass = ClearAreaUIRef.Class;
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameMode;
	SetInputMode(GameMode);
	SetShowMouseCursor(false);

	HitEffectUIWidget = CreateWidget<UPlayerHitWidget>(this, HitEffectUIClass);
	if (HitEffectUIWidget)
	{
		HitEffectUIWidget->AddToViewport();
	}

	HpBar = CreateWidget<UHpBarWidget>(this, HpBarClass);
	if (HpBar)
	{
		HpBar->AddToViewport();
	}

	AmmoCount = CreateWidget<UAmmoCountWidget>(this, AmmoCountClass);
	if (AmmoCount)
	{
		AmmoCount->AddToViewport();
	}

	CrosshairWidget = CreateWidget<UCrosshairWidget>(this, CrosshairClass);
	if (CrosshairWidget)
	{
		CrosshairWidget->AddToViewport();
	}

	ProcessUIWidget = CreateWidget<UProcessUIWidget>(this, ProcessUIClass);
	if (ProcessUIWidget)
	{
		ProcessUIWidget->AddToViewport();
		ProcessUIWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	NearbyItemUIWidget = CreateWidget<UNearbyItemWidget>(this, NearbyItemUIClass);
	if (NearbyItemUIWidget)
	{
		NearbyItemUIWidget->AddToViewport();
	}

	GameOverUIWidget = CreateWidget<UGameOverUIWidget>(this, GameOverUIClass);
	if (GameOverUIWidget)
	{
		GameOverUIWidget->AddToViewport();
		GameOverUIWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	GameClearUIWidget = CreateWidget<UGameClearWidget>(this, GameClearUIClass);
	if (GameClearUIWidget)
	{
		GameClearUIWidget->AddToViewport();
		GameClearUIWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	ClearAreaUIWidget = CreateWidget<UClearAreaUIWidget>(this, ClearAreaUIClass);
	if (ClearAreaUIWidget)
	{
		ClearAreaUIWidget->AddToViewport();
	}

	ClearAreaUIWidget->InitialAnnounce();
}

void AMyPlayerController::InitWidget(APlayerCharacter* InPlayerCharacter)
{
	HpBar->SetDelegate(InPlayerCharacter);
	AmmoCount->SetDelegate(InPlayerCharacter);
	CrosshairWidget->SetDelegate(InPlayerCharacter);
	NearbyItemUIWidget->SetDelegate(InPlayerCharacter);
	HitEffectUIWidget->SetDelegate(InPlayerCharacter);
}

void AMyPlayerController::ShowProcessUI(FText Text, float Time)
{
	ProcessUIWidget->SetVisibility(ESlateVisibility::Visible);
	ProcessUIWidget->SetProcessData(Text, Time);

	GetWorld()->GetTimerManager().SetTimer(ProcessHandle, FTimerDelegate::CreateLambda(
		[&]() {
			ProcessUIWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	), Time, false);
}

void AMyPlayerController::StopProcessUI()
{
	if (ProcessHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ProcessHandle);
	}

	ProcessUIWidget->StopProcess();
	ProcessUIWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AMyPlayerController::UpdateAmmoUIColor(EHandType NewHandType)
{
	AmmoCount->UpdateAmmoUIColor(NewHandType);
}

void AMyPlayerController::GameOver()
{
	// Hide some UI
	if (ProcessUIWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		ProcessUIWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	CrosshairWidget->SetVisibility(ESlateVisibility::Hidden);

	// Show GameOver UI
	GameOverUIWidget->SetVisibility(ESlateVisibility::Visible);
	GameOverUIWidget->GameOver();

	// InputMode change
	FInputModeUIOnly GameMode;
	SetInputMode(GameMode);
	SetShowMouseCursor(true);
}

void AMyPlayerController::GameClear()
{
	// Hide UI
	if (ProcessUIWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		ProcessUIWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	CrosshairWidget->SetVisibility(ESlateVisibility::Hidden);
	HpBar->SetVisibility(ESlateVisibility::Hidden);
	AmmoCount->SetVisibility(ESlateVisibility::Hidden);
	HitEffectUIWidget->SetVisibility(ESlateVisibility::Hidden);
	HideClearAreaUI();

	// Show GameClear UI
	AMyGameMode* Mode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameClearUIWidget->SetClearUI(Mode->GetSurvivalTime(), Mode->GetKillCount(), Mode->IsBestTime());
	GameClearUIWidget->SetVisibility(ESlateVisibility::Visible);

	// InputMode change
	FInputModeUIOnly GameMode;
	SetInputMode(GameMode);
	SetShowMouseCursor(true);
}

void AMyPlayerController::ShowClearAreaUI(int32 NewTime)
{
	ClearAreaUIWidget->ShowProcess(NewTime);
}

void AMyPlayerController::HideClearAreaUI()
{
	ClearAreaUIWidget->HideProcess();
}

void AMyPlayerController::SetLowHealthFilter(bool IsLowHealth)
{
	HitEffectUIWidget->SetLowHealthFilter(IsLowHealth);
}

void AMyPlayerController::EndAnnounce()
{
	ClearAreaUIWidget->EndAnnounce();
}
