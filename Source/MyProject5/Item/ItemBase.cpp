// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Player/PlayerCharacter.h"

// Sets default values
AItemBase::AItemBase()
{
	// Collision
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnEndOverlap);
	SphereComponent->SetSphereRadius(10.0f);
}

void AItemBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetNearbyItem(this);
	}
}

void AItemBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->RemoveNearbyItem(this);
	}
}
