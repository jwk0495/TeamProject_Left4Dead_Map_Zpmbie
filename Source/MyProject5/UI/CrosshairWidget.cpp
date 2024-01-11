// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CrosshairWidget.h"
#include "CrosshairWidget.h"
#include "Components/Image.h"
#include "Player/PlayerCharacter.h"
#include "Components/CanvasPanelSlot.h"

UCrosshairWidget::UCrosshairWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCrosshairWidget::NativeConstruct()
{
	CrossUp = Cast<UImage>(GetWidgetFromName(TEXT("CrosshairUp")));
	ensure(CrossUp);

	CrossDown = Cast<UImage>(GetWidgetFromName(TEXT("CrosshairDown")));
	ensure(CrossDown);

	CrossLeft = Cast<UImage>(GetWidgetFromName(TEXT("CrosshairLeft")));
	ensure(CrossLeft);

	CrossRight = Cast<UImage>(GetWidgetFromName(TEXT("CrosshairRight")));
	ensure(CrossRight);

	UpSlot = Cast<UCanvasPanelSlot>(CrossUp->Slot);
	DownSlot = Cast<UCanvasPanelSlot>(CrossDown->Slot);
	LeftSlot = Cast<UCanvasPanelSlot>(CrossLeft->Slot);
	RightSlot = Cast<UCanvasPanelSlot>(CrossRight->Slot);

	UpPosition = UpSlot->GetPosition();
	DownPosition = DownSlot->GetPosition();
	LeftPosition = LeftSlot->GetPosition();
	RightPosition = RightSlot->GetPosition();
}

void UCrosshairWidget::UpdateCrosshair(float ShootAccurancy)
{
	float value = (1 - ShootAccurancy) * ExpandValue;

	UpSlot->SetPosition(UpPosition + FVector2D(0, -value));
	DownSlot->SetPosition(DownPosition + FVector2D(0, value));
	LeftSlot->SetPosition(LeftPosition + FVector2D(-value, 0));
	RightSlot->SetPosition(RightPosition + FVector2D(value, 0));
}

void UCrosshairWidget::SetDelegate(APlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->OnShootAccurancyChanged.BindUObject(this, &UCrosshairWidget::UpdateCrosshair);
	}
}
