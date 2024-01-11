// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemHealPack.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AItemHealPack::AItemHealPack()
{
	// Static Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
		Mesh->SetupAttachment(SphereComponent);
	}

	ItemData = FItemData(EItemType::Heal, HealPackCount, TEXT("힐 팩"));
}
