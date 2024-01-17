// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHitWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UPlayerHitWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPlayerHitWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UImage> HitEffectImage;

// Show Effect
protected:
	UFUNCTION()
	void ShowHItEffect();

	FTimerHandle EffectHandle;
	int32 count = 1;

	float MaxAlpha = 0.3f;
	float DeltaAlpha = 0.01f;

// Delegate
public:
	void SetDelegate(class APlayerCharacter* PlayerCharacter);
};
