// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "public/ZombieBase.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABullet::ABullet()
{
	// Sphere Component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
	SphereComponent->BodyInstance.SetCollisionProfileName(TEXT("Bullet"));
	RootComponent = SphereComponent;

	// Projectile Component
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileComponent->SetUpdatedComponent(SphereComponent);
	ProjectileComponent->InitialSpeed = 30000.0f;
	ProjectileComponent->MaxSpeed = 30000.0f;
	ProjectileComponent->ProjectileGravityScale = 0;
	ProjectileComponent->bShouldBounce = false;

	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/FPWeapon/Mesh/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
	}
	Mesh->SetupAttachment(SphereComponent);
	Mesh->SetRelativeScale3D(FVector(0.01f));

	// Decal
	static ConstructorHelpers::FClassFinder<ADecalActor> BulletMarkRef(TEXT("/Game/PKH/Decal/BP_BullerMark.BP_BullerMark_C"));
	if (BulletMarkRef.Class)
	{
		BulletMarkClass = BulletMarkRef.Class;
	}
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	ProjectileComponent->Velocity = FVector::Zero();
}

void ABullet::Fire(FVector DirectionVec, int32 NewAttackPower)
{
	ProjectileComponent->Velocity = DirectionVec * ProjectileComponent->InitialSpeed;
	AttackPower = NewAttackPower;
}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Bullet Overlap"));
	// when zombie hit
	AZombieBase* Zombie = Cast<AZombieBase>(OtherActor);
	if (Zombie)
	{
		float ImpactHeight = SweepResult.ImpactPoint.Z;
		float ZombieHeadHeight = Zombie->GetActorLocation().Z;
		UCapsuleComponent* ZombieColl = Cast<UCapsuleComponent>(OtherComp);
		if (ZombieColl)
		{
			ZombieHeadHeight += ZombieColl->GetUnscaledCapsuleHalfHeight() * 0.45f;
		}

		if (ImpactHeight >= ZombieHeadHeight) // Head Shot
		{
			Zombie->OnDamaged(AttackPower * HeadShotRate); 
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("HeadShot"));

			UParticleSystemComponent* ParticleComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodVFX, SweepResult.ImpactPoint, FRotator(0));
			ParticleComp->CustomTimeDilation = 4;
		}
		else // Normal Shot
		{
			Zombie->OnDamaged(AttackPower);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("NormalShot"));

			UParticleSystemComponent* ParticleComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodVFX, SweepResult.ImpactPoint, FRotator(0), FVector(0.5f));
			ParticleComp->CustomTimeDilation = 5;
		}

		UE_LOG(LogTemp, Log, TEXT("Bullet Hit: %d"), AttackPower);
	}
	else
	{
		UParticleSystemComponent* ParticleComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SparkVFX, SweepResult.ImpactPoint);
		ParticleComp->CustomTimeDilation = 4.0f;

		// Decal
		FActorSpawnParameters Param;
		GetWorld()->SpawnActor<ADecalActor>(BulletMarkClass, SweepResult.ImpactPoint, FRotator(0), Param);
	}

	Destroy();
}

