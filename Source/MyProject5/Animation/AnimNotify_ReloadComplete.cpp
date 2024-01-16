// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_ReloadComplete.h"
#include "Player/PlayerCharacter.h"

UAnimNotify_ReloadComplete::UAnimNotify_ReloadComplete()
{
}

void UAnimNotify_ReloadComplete::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (PlayerCharacter)
		{
			PlayerCharacter->ReloadComplete();
		}
	}
}
