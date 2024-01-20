// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "BulletMarker.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API ABulletMarker : public ADecalActor
{
	GENERATED_BODY()

public:
	ABulletMarker();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UDecalComponent> DecalComp;
	
};
