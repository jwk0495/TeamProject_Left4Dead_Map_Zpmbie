// Fill out your copyright notice in the Description page of Project Settings.


#include "Throwable/ThrowableWeaponBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "public/ZombieBase.h"
#include "Components/PointLightComponent.h"

// Sets default values
AThrowableWeaponBase::AThrowableWeaponBase()
{
	// Sphere Component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->BodyInstance.SetCollisionProfileName(TEXT("Grenade"));
	RootComponent = SphereComponent;

	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Megascans/3D_Assets/Cricket_Ball_udqlcjbva/S_Cricket_Ball_udqlcjbva_lod0_Var1.S_Cricket_Ball_udqlcjbva_lod0_Var1'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
	}
	Mesh->SetupAttachment(SphereComponent);

	// Projectile
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileComponent->ProjectileGravityScale = 1.5f;
	ProjectileComponent->InitialSpeed = 1200.0f;
	ProjectileComponent->MaxSpeed = 1200.0f;
	ProjectileComponent->bShouldBounce = true;

	// Particle
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(RootComponent);
	ParticleComponent->bAutoActivate = false;
	ParticleComponent->bAutoDestroy = true;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (ParticleRef.Object)
	{
		ParticleComponent->SetTemplate(ParticleRef.Object);
	}

	// Light
	LightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	LightComponent->SetupAttachment(SphereComponent);
	LightComponent->SetIntensity(0);
}

void AThrowableWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	ProjectileComponent->Velocity = FVector::Zero();
}

void AThrowableWeaponBase::Throw(FVector DirectionVec)
{
	ProjectileComponent->Velocity = ProjectileComponent->InitialSpeed * DirectionVec;

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AThrowableWeaponBase::Explode, ExplodeDelay, false);
}

void AThrowableWeaponBase::Explode()
{
	TArray<FOverlapResult> OverlapResults;

	bool IsHit = GetWorld()->OverlapMultiByProfile(OverlapResults, GetActorLocation(), FQuat::Identity,
									               TEXT("Enemy"), FCollisionShape::MakeSphere(ExplodeRadius));

	DrawDebugSphere(GetWorld(), GetActorLocation(), ExplodeRadius, 16, FColor::Red, false, 0.5f);
	ParticleComponent->SetActive(true);

	if (IsHit)
	{
		for (int i = 0; i < OverlapResults.Num(); i++)
		{
			// Check Zombie
			AZombieBase* Zombie = Cast<AZombieBase>(OverlapResults[i].GetActor());
			if (Zombie)
			{
				Zombie->OnDamaged(AttackPower);
				UE_LOG(LogTemp, Log, TEXT("Explode Hit: %d"), AttackPower);
			}
		}
	}
	
	// Destroy
	FTimerHandle DestroyHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda(
		[&]() {
			Destroy();
		}
	), 2.0f, false);

	// Light
	LightComponent->SetIntensity(MaxIntensity);

	FTimerHandle LightHandle;
	GetWorld()->GetTimerManager().SetTimer(LightHandle, FTimerDelegate::CreateLambda(
		[&]() {
			LightComponent->SetIntensity(MaxIntensity - DeltaLightIntensity * count);
			count++;
		}
	), 0.05f, true);
}


