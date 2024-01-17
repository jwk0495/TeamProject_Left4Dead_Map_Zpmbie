// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_MeleeAttackEnd.h"
#include "Player/PlayerCharacter.h"

UAnimNotify_MeleeAttackEnd::UAnimNotify_MeleeAttackEnd()
{
}

void UAnimNotify_MeleeAttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (PlayerCharacter)
		{
			PlayerCharacter->MeleeAttackEnd();
		}
	}
}
