// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_HealEnd.h"
#include "Player/PlayerCharacter.h"

UAnimNotify_HealEnd::UAnimNotify_HealEnd()
{
}

void UAnimNotify_HealEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (PlayerCharacter)
		{
			PlayerCharacter->HealEnd();
		}
	}
}
