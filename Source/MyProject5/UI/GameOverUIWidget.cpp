// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverUIWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

UGameOverUIWidget::UGameOverUIWidget(const FObjectInitializer& ObjectInitilaizer) : Super(ObjectInitilaizer)
{
}

void UGameOverUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameOverText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GameOver")));
	ensure(GameOverText);

	Button_Restart = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Restart")));
	ensure(Button_Restart);

	Button_Exit = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Exit")));
	ensure(Button_Exit);
}
