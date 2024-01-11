// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UGameOverUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGameOverUIWidget(const FObjectInitializer& ObjectInitilaizer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<class UTextBlock> GameOverText;

	UPROPERTY()
	TObjectPtr<class UButton> Button_Restart;

	UPROPERTY()
	TObjectPtr<class UButton> Button_Exit;
};
