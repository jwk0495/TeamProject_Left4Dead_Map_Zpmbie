// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameClearWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

UGameClearWidget::UGameClearWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UGameClearWidget::NativeConstruct()
{
	ClearTimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ClearTimeTxt")));
	ensure(ClearTimeText);

	KillCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("KillCountTxt")));
	ensure(KillCountText);

	RestartButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Restart")));
	ensure(RestartButton);

	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Exit")));
	ensure(ExitButton);
}

void UGameClearWidget::SetClearUI(int32 Seconds, int32 KillCount)
{
	int Min = Seconds / 60;
	int Sec = Seconds % 60;
	FString MinStr = Min < 10 ? FString::Printf(TEXT("0%d"), Min) : FString::Printf(TEXT("%d"), Min);
	FString SecStr = Sec < 10 ? FString::Printf(TEXT("0%d"), Sec) : FString::Printf(TEXT("%d"), Sec);
	ClearTimeText->SetText(FText::FromString(FString::Printf(TEXT("생존 시간 - %s:%s"), *MinStr, *SecStr)));
	KillCountText->SetText(FText::FromString(FString::Printf(TEXT("처치한 좀비 수 - %d"), KillCount)));
}
