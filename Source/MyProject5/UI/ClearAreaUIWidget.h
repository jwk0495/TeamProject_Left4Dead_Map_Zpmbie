// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClearAreaUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UClearAreaUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UClearAreaUIWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<class UTextBlock> LeftTimeText;

	int32 LeftTime;

	FTimerHandle TextHandle;

public:
	void ShowProcess(int32 NewLeftTime);
	void HideProcess();
	
};
