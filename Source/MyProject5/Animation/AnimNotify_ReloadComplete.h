// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ReloadComplete.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UAnimNotify_ReloadComplete : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_ReloadComplete();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
