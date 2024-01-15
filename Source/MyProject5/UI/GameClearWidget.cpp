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
	ClearTimeText->SetText(FText::FromString(FString::Printf(TEXT("���� �ð� - %d:%d"), Seconds / 60, Seconds % 60)));
	KillCountText->SetText(FText::FromString(FString::Printf(TEXT("óġ�� ���� �� - %d"), KillCount)));
}
