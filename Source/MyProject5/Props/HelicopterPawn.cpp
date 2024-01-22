// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/HelicopterPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
AHelicopterPawn::AHelicopterPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);
	MeshComponent->SetWorldScale3D(FVector(4));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/PKH/Mesh/ka27.ka27'"));
	if (MeshRef.Object)
	{
		MeshComponent->SetSkeletalMesh(MeshRef.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/PKH/AnimationStarter/Helicopter/BP_HelicopterAnim.BP_HelicopterAnim_C"));
	if (AnimInstanceRef.Class)
	{
		MeshComponent->SetAnimClass(AnimInstanceRef.Class);
	}

	// Camera
	HelicopterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("HelicopterCamera"));
	HelicopterCamera->SetupAttachment(MeshComponent);
	HelicopterCamera->AddRelativeLocation(FVector(0, -121, 83));
	HelicopterCamera->AddRelativeRotation(FRotator(-30, 90, 0));
}

// Called when the game starts or when spawned
void AHelicopterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHelicopterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (false == IsLanded)
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), LandLocation, DeltaTime, 1.0f));
		if (FVector::Distance(GetActorLocation(), LandLocation) < 10.0f)
		{
			IsLanded = true;
		}
	}
	else
	{
		FVector NextLocation = FMath::VInterpTo(GetActorLocation(), DestLocation, DeltaTime, 0.3f);
		FVector Diff = NextLocation - GetActorLocation();
		SetActorLocation(NextLocation);

		HelicopterCamera->AddRelativeLocation(Diff * DeltaTime);
		HelicopterCamera->SetRelativeRotation(FMath::RInterpTo(FRotator(-30, 90, 0), FRotator(30, 90, 0), DeltaTime, 0.3f));
	}
}


