// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/ClearArea.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Player/PlayerCharacter.h"

// Sets default values
AClearArea::AClearArea()
{
	ClearCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SpherComponent"));
	ClearCollision->SetupAttachment(RootComponent);
	ClearCollision->OnComponentBeginOverlap.AddDynamic(this, &AClearArea::OnBeginOverlap);
	ClearCollision->OnComponentEndOverlap.AddDynamic(this, &AClearArea::OnEndOverlap);

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(ClearCollision);
	ParticleComponent->bAutoActivate = true;
	ParticleComponent->bAutoDestroy = false;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleRef(TEXT(""));
	if (ParticleRef.Object)
	{
		ParticleComponent->SetTemplate(ParticleRef.Object);
	}

}

void AClearArea::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (nullptr == PlayerCharacter)
	{
		return;
	}

	Player = PlayerCharacter;
	GetWorld()->GetTimerManager().SetTimer(ClearHandle, FTimerDelegate::CreateLambda(
		[&]() {
			Player->GameClear();
		}
	), 3.0f, false);
}

void AClearArea::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (nullptr == PlayerCharacter)
	{
		return;
	}

	if (ClearHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ClearHandle);
	}
	Player = nullptr;
}

