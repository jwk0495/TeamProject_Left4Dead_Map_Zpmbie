// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGame_BestTime.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API USaveGame_BestTime : public USaveGame
{
	GENERATED_BODY()
	
protected:
	int32 BestSeconds;

public:
	FORCEINLINE int32 GetBestSeconds() const { return BestSeconds; }
	FORCEINLINE void SetBestSeconds(int32 NewBestSeconds) { BestSeconds = NewBestSeconds; }
};
