// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "ItemHealPack.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API AItemHealPack : public AItemBase
{
	GENERATED_BODY()
	
public:
	AItemHealPack();

protected:
	int32 HealPackCount = 1;
};
