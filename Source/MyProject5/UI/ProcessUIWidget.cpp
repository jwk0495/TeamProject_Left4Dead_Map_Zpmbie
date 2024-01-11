// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ProcessUIWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/ProgressBar.h"

UProcessUIWidget::UProcessUIWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UProcessUIWidget::NativeConstruct()
{
	ProcessText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ProcessTxt")));
	ensure(ProcessText);
	
	ProcessProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProcessBar")));
	ensure(ProcessProgressBar);
}

void UProcessUIWidget::SetProcessData(FText Text, float InTime)
{
	ProcessText->SetText(Text);
	MaxProcessTime = InTime;
	GetWorld()->GetTimerManager().SetTimer(ProcessHandle, this, &UProcessUIWidget::SetProcess, GetWorld()->GetDeltaSeconds(), true);
}

void UProcessUIWidget::SetProcess()
{
	CurProcessTime += GetWorld()->GetDeltaSeconds();
	ProcessProgressBar->SetPercent(CurProcessTime / MaxProcessTime);

	if (CurProcessTime >= MaxProcessTime)
	{
		GetWorld()->GetTimerManager().ClearTimer(ProcessHandle);
		ProcessProgressBar->SetPercent(0);
		CurProcessTime = 0;
	}
}
