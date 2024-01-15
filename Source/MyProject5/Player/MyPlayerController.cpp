// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MyPlayerController.h"
#include "UI/HpBarWidget.h"
#include "UI/AmmoCountWidget.h"
#include "UI/CrosshairWidget.h"
#include "UI/ProcessUIWidget.h"
#include "UI/GameOverUIWidget.h"
#include "UI/NearbyItemWidget.h"

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

	static ConstructorHelpers::FClassFinder<UGameOverUIWidget> GameOverUIRef(TEXT("/Game/PKH/UI/WBP_GameOverUI.WBP_GameOverUI_C"));
	if (GameOverUIRef.Class)
	{
		GameOverUIClass = GameOverUIRef.Class;
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameMode;
	SetInputMode(GameMode);
	SetShowMouseCursor(false);

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
}

void AMyPlayerController::InitWidget(APlayerCharacter* InPlayerCharacter)
{
	HpBar->SetDelegate(InPlayerCharacter);
	AmmoCount->SetDelegate(InPlayerCharacter);
	CrosshairWidget->SetDelegate(InPlayerCharacter);
	NearbyItemUIWidget->SetDelegate(InPlayerCharacter);
}

void AMyPlayerController::ShowProcessUI(FText Text, float Time)
{
	ProcessUIWidget->SetVisibility(ESlateVisibility::Visible);
	ProcessUIWidget->SetProcessData(Text, Time);

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda(
		[&]() {
			ProcessUIWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	), Time, false);
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

	// InputMode change
	FInputModeUIOnly GameMode;
	SetInputMode(GameMode);
	SetShowMouseCursor(true);
}
