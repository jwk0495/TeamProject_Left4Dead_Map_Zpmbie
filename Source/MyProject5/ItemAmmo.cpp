// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemAmmo.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AItemAmmo::AItemAmmo()
{
	// Static Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
	}

	ItemData = FItemData(EItemType::Ammo, AmmoValue, TEXT("탄창"));
}
