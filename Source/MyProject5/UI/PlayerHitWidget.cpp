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
	HitEffectImage->ColorAndOpacity.A = 0;
}

void UPlayerHitWidget::ShowHItEffect()
{
	if (EffectHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(EffectHandle);
		count = 1;
	}

	HitEffectImage->ColorAndOpacity.A = MaxAlpha; UE_LOG(LogTemp, Log, TEXT("Hit Effect"));
	GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda(
		[&]() {
			HitEffectImage->ColorAndOpacity.A = MaxAlpha - (count * DeltaAlpha);
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
