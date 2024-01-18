// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHitWidget.h"
#include "Components/Image.h"
#include "Player/PlayerCharacter.h"

UPlayerHitWidget::UPlayerHitWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UPlayerHitWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HitEffectImage = Cast<UImage>(GetWidgetFromName(TEXT("HitEffectImg")));
	ensure(HitEffectImage);
	HitEffectImage->SetOpacity(0);
}

void UPlayerHitWidget::ShowHItEffect(bool IsDead)
{
	StopEffectTimer();
	StopResetTimer();

	if (IsDead)
	{
		HitEffectImage->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	HitEffectImage->SetOpacity(MaxAlpha);
	GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda(
		[&]() {
			HitEffectImage->SetOpacity(MaxAlpha - (Count * DeltaAlpha));
			Count++;
		}
	), 0.1f, true);
	
	GetWorld()->GetTimerManager().SetTimer(StopHandle, FTimerDelegate::CreateLambda(
		[&]() {
			StopEffectTimer();
		}
	),MaxAlpha / DeltaAlpha, false);
}

void UPlayerHitWidget::StopEffectTimer()
{
	if (EffectHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(EffectHandle);
		Count = 1;
	}
}

void UPlayerHitWidget::StopResetTimer()
{
	if (StopHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(StopHandle);
	}
}

void UPlayerHitWidget::SetDelegate(class APlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->OnPlayerDamaged.BindUObject(this, &UPlayerHitWidget::ShowHItEffect);
	}
}
