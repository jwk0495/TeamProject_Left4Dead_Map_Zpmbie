// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverUIWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Game/MyGameMode.h"

UGameOverUIWidget::UGameOverUIWidget(const FObjectInitializer& ObjectInitilaizer) : Super(ObjectInitilaizer)
{
}

void UGameOverUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SurvivalTimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SurvivalTimeTxt")));
	ensure(SurvivalTimeText);

	KillCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("KillCountTxt")));
	ensure(KillCountText);

	Button_Restart = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Restart")));
	ensure(Button_Restart);

	Button_Exit = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Exit")));
	ensure(Button_Exit);
}

void UGameOverUIWidget::GameOver()
{
	AMyGameMode* GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (nullptr == GameMode)
	{
		return;
	}

	int Seconds = GameMode->GetSurvivalTime();
	int Min = Seconds / 60;
	int Sec = Seconds % 60;
	FString MinStr = Min < 10 ? FString::Printf(TEXT("0%d"), Min) : FString::Printf(TEXT("%d"), Min);
	FString SecStr = Sec < 10 ? FString::Printf(TEXT("0%d"), Sec) : FString::Printf(TEXT("%d"), Sec);

	SurvivalTimeText->SetText(FText::FromString(FString::Printf(TEXT("생존 시간 - %s:%s"), *MinStr, *SecStr)));
	KillCountText->SetText(FText::FromString(FString::Printf(TEXT("처치한 좀비 수 - %d"), GameMode->GetKillCount())));
}
