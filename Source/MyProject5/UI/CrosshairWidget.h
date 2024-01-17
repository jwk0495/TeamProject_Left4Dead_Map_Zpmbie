// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCrosshairWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	void UpdateCrosshair(float ShootAccurancy);

	// Images
	UPROPERTY()
	TObjectPtr<class UImage> CrossUp;

	UPROPERTY()
	TObjectPtr<class UImage> CrossDown;

	UPROPERTY()
	TObjectPtr<class UImage> CrossLeft;

	UPROPERTY()
	TObjectPtr<class UImage> CrossRight;

	// Slots
	UPROPERTY()
	TObjectPtr<class UCanvasPanelSlot> UpSlot;

	UPROPERTY()
	TObjectPtr<class UCanvasPanelSlot> DownSlot;

	UPROPERTY()
	TObjectPtr<class UCanvasPanelSlot> LeftSlot;

	UPROPERTY()
	TObjectPtr<class UCanvasPanelSlot> RightSlot;

	FVector2D UpPosition;
	FVector2D DownPosition;
	FVector2D LeftPosition;
	FVector2D RightPosition;

	float ExpandValue = 60.0f;

public:
	void SetDelegate(class APlayerCharacter* PlayerCharacter);
};
