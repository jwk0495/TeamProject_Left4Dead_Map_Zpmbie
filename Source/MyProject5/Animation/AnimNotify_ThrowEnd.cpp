// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_ThrowEnd.h"
#include "Player/PlayerCharacter.h"

UAnimNotify_ThrowEnd::UAnimNotify_ThrowEnd()
{
}

void UAnimNotify_ThrowEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (PlayerCharacter)
		{
			PlayerCharacter->ThrowEnd();
		}
	}
}
