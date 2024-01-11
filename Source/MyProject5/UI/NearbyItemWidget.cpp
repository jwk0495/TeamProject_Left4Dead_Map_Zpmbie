// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NearbyItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Player/PlayerCharacter.h"

UNearbyItemWidget::UNearbyItemWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UNearbyItemWidget::NativeConstruct()
{
	ItemText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NearbyItemText")));
	ensure(ItemText);

	ButtonIcon = Cast<UImage>(GetWidgetFromName(TEXT("GetButtonIcon")));
	ensure(ButtonIcon);

	ItemText->SetVisibility(ESlateVisibility::Hidden);
	ButtonIcon->SetVisibility(ESlateVisibility::Hidden);
}

void UNearbyItemWidget::UpdateItemText(bool IsExist, FText NewItemText)
{
	if (IsExist)
	{
		ItemText->SetText(NewItemText);
		ItemText->SetVisibility(ESlateVisibility::Visible);
		ButtonIcon->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ItemText->SetVisibility(ESlateVisibility::Hidden);
		ButtonIcon->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UNearbyItemWidget::SetDelegate(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->OnNearbyItemChanged.BindUObject(this, &UNearbyItemWidget::UpdateItemText);
}
