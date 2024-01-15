// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ThrowGrenade.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UAnimNotify_ThrowGrenade : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_ThrowGrenade();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
