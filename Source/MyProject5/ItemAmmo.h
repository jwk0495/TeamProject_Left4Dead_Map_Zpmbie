// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "ItemAmmo.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API AItemAmmo : public AItemBase
{
	GENERATED_BODY()
	
public:
	AItemAmmo();

protected:
	int32 AmmoValue = 50;
};
