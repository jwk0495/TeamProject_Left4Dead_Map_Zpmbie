// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoCountWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UAmmoCountWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UAmmoCountWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<class UTextBlock> MainAmmoText;

	UPROPERTY()
	TObjectPtr<class UTextBlock> SubAmmoText;

	UPROPERTY()
	TObjectPtr<class UTextBlock> GrenadeText;

	UPROPERTY()
	TObjectPtr<class UTextBlock> HealPackText;

public:
	UFUNCTION()
	void UpdateMainAmmoCount(int32 NewCurAmmo, int32 NewRemainAmmo);

	UFUNCTION()
	void UpdateSubAmmoCount(int32 NewCurAmmo);

	UFUNCTION()
	void UpdateGrenadeCount(int32 NewRemainGrenade);

	UFUNCTION()
	void UpdateHealPackCount(int32 NewRemainGrenade);

	void SetDelegate(class APlayerCharacter* PlayerCharacter);
};
