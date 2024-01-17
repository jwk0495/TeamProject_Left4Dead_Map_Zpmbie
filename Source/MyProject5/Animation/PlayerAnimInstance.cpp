// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	MoveThreshold = 3.0f;
	RunThreshold = 300.0f;
	JumpThreshold = 100.0f;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningPlayer = Cast<APlayerCharacter>(GetOwningActor());
	if (OwningPlayer)
	{
		PlayerMovement = OwningPlayer->GetCharacterMovement();
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (nullptr == PlayerMovement)
	{
		return;
	}

	MoveVelocity = PlayerMovement->Velocity;
	GroundSpeed = MoveVelocity.Size2D();
	bIsIdle = (GroundSpeed < MoveThreshold);
	bIsFalling = PlayerMovement->IsFalling();
	bIsJumping = (bIsFalling & (MoveVelocity.Z > JumpThreshold));
	bIsFiring = OwningPlayer->GetIsFiring();

	bIsMainWeapon = OwningPlayer->GetIsMainWeapon();
	bIsSubWeapon = OwningPlayer->GetIsSubWeapon();
	bIsGrenade = OwningPlayer->GetIsGrenade();
	bIsHealPack = OwningPlayer->GetIsHealPack();

	bIsDead = OwningPlayer->GetIsDead();
}
