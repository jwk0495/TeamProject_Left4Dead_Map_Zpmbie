// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_ThrowGrenade.h"
#include "Player/PlayerCharacter.h"

UAnimNotify_ThrowGrenade::UAnimNotify_ThrowGrenade()
{

}

void UAnimNotify_ThrowGrenade::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (PlayerCharacter)
		{
			PlayerCharacter->ThrowGrenade();
		}
	}
}
