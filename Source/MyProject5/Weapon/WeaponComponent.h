// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UWeaponComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

protected:
	UPROPERTY()
	TObjectPtr<class UStaticMesh> WeaponMesh;


	
};
