// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UGameClearWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGameClearWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<class UTextBlock> ClearTimeText;

	UPROPERTY()
	TObjectPtr<class UTextBlock> KillCountText;

	UPROPERTY()
	TObjectPtr<class UButton> RestartButton;

	UPROPERTY()
	TObjectPtr<class UButton> ExitButton;

public:
	void SetClearUI(int32 Seconds, int32 KillCount);
};
