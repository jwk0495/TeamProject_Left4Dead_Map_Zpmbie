// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/ClearArea.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Player/PlayerCharacter.h"
#include "Player/MyPlayerController.h"

// Sets default values
AClearArea::AClearArea()
{
	ClearCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SpherComponent"));
	ClearCollision->SetupAttachment(RootComponent);
	ClearCollision->OnComponentBeginOverlap.AddDynamic(this, &AClearArea::OnBeginOverlap);
	ClearCollision->OnComponentEndOverlap.AddDynamic(this, &AClearArea::OnEndOverlap);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(ClearCollision);
}

void AClearArea::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (nullptr == PlayerCharacter)
	{
		return;
	}

	// UI
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		PlayerController->ShowClearAreaUI(ClearTime);
	}

	Player = PlayerCharacter;
	GetWorldTimerManager().SetTimer(ClearHandle, FTimerDelegate::CreateLambda(
		[&]() {
			Player->GameClear();
		}
	), ClearTime, false);
}

void AClearArea::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (nullptr == PlayerCharacter)
	{
		return;
	}

	// UI
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		PlayerController->HideClearAreaUI();
	}

	if (ClearHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(ClearHandle);
	}
	Player = nullptr;
}

