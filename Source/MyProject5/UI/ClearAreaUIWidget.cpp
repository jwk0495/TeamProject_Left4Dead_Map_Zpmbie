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
	LeftTimeText->SetVisibility(ESlateVisibility::Visible);

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
	LeftTimeText->SetVisibility(ESlateVisibility::Hidden);
}

void UClearAreaUIWidget::InitialAnnounce()
{
	LeftTimeText->SetText(FText::FromString(FString::Printf(TEXT("목표: 랑데부 포인트를 향해 전진하라"))));

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda(
		[&]() {
			LeftTimeText->SetVisibility(ESlateVisibility::Hidden);
		}), 5.0f, false);
}
