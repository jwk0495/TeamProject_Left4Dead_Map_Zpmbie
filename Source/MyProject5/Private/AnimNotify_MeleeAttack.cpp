// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_MeleeAttack.h"
#include "Player/PlayerCharacter.h"

UAnimNotify_MeleeAttack::UAnimNotify_MeleeAttack()
{
}

void UAnimNotify_MeleeAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (PlayerCharacter)
		{
			PlayerCharacter->MeleeAttackHit();
		}
	}
}
