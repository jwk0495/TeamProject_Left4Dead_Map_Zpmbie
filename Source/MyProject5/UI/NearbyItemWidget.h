// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NearbyItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UNearbyItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UNearbyItemWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<class UTextBlock> ItemText;

	UPROPERTY()
	TObjectPtr<class UImage> ButtonIcon;

public:
	UFUNCTION()
	void UpdateItemText(bool IsExist, FText NewItemText);

	void SetDelegate(class APlayerCharacter* PlayerCharacter);
};
