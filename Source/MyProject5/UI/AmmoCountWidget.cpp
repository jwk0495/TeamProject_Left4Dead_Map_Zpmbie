// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AmmoCountWidget.h"
#include "Components/TextBlock.h"
#include "Player/PlayerCharacter.h"
#include "Player/MyPlayerController.h"

UAmmoCountWidget::UAmmoCountWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UAmmoCountWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MainAmmoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MainAmmo")));
	ensure(MainAmmoText);

	SubAmmoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SubAmmo")));
	ensure(SubAmmoText);

	GrenadeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Grenade")));
	ensure(GrenadeText);

	HealPackText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HealPack")));
	ensure(HealPackText);
}

void UAmmoCountWidget::UpdateMainAmmoCount(int32 NewCurAmmo, int32 NewRemainAmmo)
{
	MainAmmoText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), NewCurAmmo, NewRemainAmmo)));
}

void UAmmoCountWidget::UpdateSubAmmoCount(int32 NewCurAmmo)
{
	SubAmmoText->SetText(FText::FromString(FString::Printf(TEXT("%d / ∞"), NewCurAmmo)));
}

void UAmmoCountWidget::UpdateGrenadeCount(int32 NewRemainGrenade)
{
	GrenadeText->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewRemainGrenade)));
}

void UAmmoCountWidget::UpdateHealPackCount(int32 NewRemainHealPack)
{
	HealPackText->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewRemainHealPack)));
}

void UAmmoCountWidget::UpdateAmmoUIColor(EHandType NewHandType)
{
	switch (NewHandType)
	{
	case EHandType::MainWeapon:
		MainAmmoText->SetColorAndOpacity(FLinearColor(0.3f, 1, 0));
		SubAmmoText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		GrenadeText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		HealPackText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		break;
	case EHandType::SubWeapon:
		MainAmmoText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		SubAmmoText->SetColorAndOpacity(FLinearColor(0.3f, 1, 0));
		GrenadeText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		HealPackText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		break;
	case EHandType::Grenade:
		MainAmmoText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		SubAmmoText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		GrenadeText->SetColorAndOpacity(FLinearColor(0.3f, 1, 0));
		HealPackText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		break;
	case EHandType::HealPack:
		MainAmmoText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		SubAmmoText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		GrenadeText->SetColorAndOpacity(FLinearColor(1, 1, 1));
		HealPackText->SetColorAndOpacity(FLinearColor(0.3f, 1, 0));
		break;
	}
}

void UAmmoCountWidget::SetDelegate(APlayerCharacter* PlayerCharacter)
{
	// Delegate Bind
	if (PlayerCharacter)
	{
		PlayerCharacter->OnMainAmmoChanged.BindUObject(this, &UAmmoCountWidget::UpdateMainAmmoCount);
		PlayerCharacter->OnSubAmmoChanged.BindUObject(this, &UAmmoCountWidget::UpdateSubAmmoCount);
		PlayerCharacter->OnGrenadeChanged.BindUObject(this, &UAmmoCountWidget::UpdateGrenadeCount);
		PlayerCharacter->OnHealPackChanged.BindUObject(this, &UAmmoCountWidget::UpdateHealPackCount);
	}
}
