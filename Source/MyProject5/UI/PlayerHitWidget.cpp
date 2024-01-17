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

void UPlayerHitWidget::ShowHItEffect()
{
	if (EffectHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(EffectHandle);
		Count = 1;
	}

	HitEffectImage->SetOpacity(MaxAlpha);
	GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda(
		[&]() {
			HitEffectImage->SetOpacity(MaxAlpha - (Count * DeltaAlpha));
			Count++;
		}
	), 0.1f, true);
}

void UPlayerHitWidget::SetDelegate(class APlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->OnPlayerDamaged.BindUObject(this, &UPlayerHitWidget::ShowHItEffect);
	}
}
