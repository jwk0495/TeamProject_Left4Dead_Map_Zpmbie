// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/BulletMarker.h"
#include "Components/DecalComponent.h"

ABulletMarker::ABulletMarker()
{
	DecalComp = GetDecal();

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialRef(TEXT("/Script/Engine.Material'/Game/PKH/Material/M_BulletMark.M_BulletMark'"));
	if (MaterialRef.Object)
	{
		DecalComp->SetMaterial(0, MaterialRef.Object);
	}
}
