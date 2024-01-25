// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProcessUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UProcessUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UProcessUIWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<class UTextBlock> ProcessText;

	UPROPERTY()
	TObjectPtr<class UProgressBar> ProcessProgressBar;

protected:
	UFUNCTION()
	void SetProcess();

	FTimerHandle ProcessHandle;

	float CurProcessTime = 0;
	float MaxProcessTime = 0;

public:
	void SetProcessData(FText Text, float Time);

	void StopProcess();
};
