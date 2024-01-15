// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyGameMode();

protected:
	virtual void BeginPlay() override;

	int32 SurvivalTime = 0;
	int32 KillCount = 0;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void KillCountPlus() { KillCount++; }

	FORCEINLINE int32 GetSurvivalTime() const { return SurvivalTime; }
	FORCEINLINE int32 GetKillCount() const { return KillCount; }
};
