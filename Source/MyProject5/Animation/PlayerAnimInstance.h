// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	TObjectPtr<class APlayerCharacter> OwningPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	TObjectPtr<class UCharacterMovementComponent> PlayerMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	FVector MoveVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	float MoveThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	float RunThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	float JumpThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	uint8 bIsJumping : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	uint8 bIsFalling : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	uint8 bIsFiring : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	uint8 bIsMainWeapon: 1;
};
