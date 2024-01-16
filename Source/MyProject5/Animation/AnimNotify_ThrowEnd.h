// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ThrowEnd.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UAnimNotify_ThrowEnd : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_ThrowEnd();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
