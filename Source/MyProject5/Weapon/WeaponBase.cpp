// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "Components/SceneComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SceneComponent->SetupAttachment(RootComponent);

	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComponent"));
	WeaponMeshComponent->SetupAttachment(SceneComponent);
}

UStaticMesh* AWeaponBase::GetWeaponStaticMesh()
{
	UStaticMesh* StaticMesh = WeaponMeshComponent->GetStaticMesh();
	if (StaticMesh)
	{
		return StaticMesh;
	}
	return nullptr;
}
