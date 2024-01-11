// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Player/PlayerCharacter.h"
#include "Player/MyPlayerController.h"

UHpBarWidget::UHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UHpBarWidget::NativeConstruct()
{
	HpBarWidget = Cast<UProgressBar>(GetWidgetFromName(TEXT("HpBar")));
	ensure(HpBarWidget);
	
}

void UHpBarWidget::UpdateHpBar(float HpRate)
{
	HpBarWidget->SetPercent(HpRate);
}

void UHpBarWidget::SetDelegate(APlayerCharacter* PlayerCharacter)
{
	// Delegate Bind
	if (PlayerCharacter)
	{
		PlayerCharacter->OnHpChanged.BindUObject(this, &UHpBarWidget::UpdateHpBar);
	}
}
