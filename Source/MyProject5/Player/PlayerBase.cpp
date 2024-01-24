// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SpotLightComponent.h"

// Sets default values
APlayerBase::APlayerBase()
{
	// Camera
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->AirControl = 10.0f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 100.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -100), FRotator(0, -90, 0));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	// Weapon Component
	WeaponComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	WeaponComponent->AddRelativeLocation(FVector(0, 30, 110));
	WeaponComponent->SetCollisionProfileName(TEXT("NoCollision"));
		
	// Set SkeletalMesh & AnimInstance
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (MeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/PKH/AnimationStarter/ABP_Player.ABP_Player_C"));
	if (AnimInstanceRef.Class)
	{
		GetMesh()->SetAnimClass(AnimInstanceRef.Class);
	}

	// GunShot Particle
	GunShotParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GunShotParticle"));
	GunShotParticleComponent->SetupAttachment(WeaponComponent, TEXT("FireSocket"));
	GunShotParticleComponent->bAutoActivate = false;
	GunShotParticleComponent->bAutoDestroy = false;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Gruntling/Master/P_BackPack_MuzzleFlash.P_BackPack_MuzzleFlash'"));
	if (ParticleRef.Object)
	{
		GunShotParticleComponent->SetTemplate(ParticleRef.Object);
	}

	SpotLightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLightComp->SetupAttachment(WeaponComponent, TEXT("FireSocket"));
	SpotLightComp->SetRelativeLocation(FVector::ZeroVector);
	SpotLightComp->SetIntensity(15000);
	SpotLightComp->SetAttenuationRadius(1700);
	SpotLightComp->SetOuterConeAngle(12);
}

