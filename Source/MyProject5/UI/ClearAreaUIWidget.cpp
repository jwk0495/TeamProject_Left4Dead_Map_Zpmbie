// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ClearAreaUIWidget.h"
#include "Components/TextBlock.h"

UClearAreaUIWidget::UClearAreaUIWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UClearAreaUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LeftTimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("LeftTimeTxt")));
	ensure(LeftTimeText);
}

void UClearAreaUIWidget::ShowProcess(int32 NewLeftTime)
{
	if (TextHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TextHandle);
	}

	LeftTimeText->SetText(FText::FromString(FString::Printf(TEXT("구조까지 남은 시간: %d초"), NewLeftTime)));
	LeftTime = NewLeftTime;

	GetWorld()->GetTimerManager().SetTimer(TextHandle, FTimerDelegate::CreateLambda(
		[&]() {
			--LeftTime;
			LeftTimeText->SetText(FText::FromString(FString::Printf(TEXT("구조까지 남은 시간: %d초"), LeftTime)));
		}), 1.0f, true, 1.0f);
}

void UClearAreaUIWidget::HideProcess()
{
	if (TextHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TextHandle);
	}
}
