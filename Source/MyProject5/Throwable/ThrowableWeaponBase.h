// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowableWeaponBase.generated.h"

UCLASS()
class MYPROJECT5_API AThrowableWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AThrowableWeaponBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UParticleSystemComponent> ParticleComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPointLightComponent> LightComponent;

	UPROPERTY(EditAnywhere)
	int32 AttackPower = 0;

	float ExplodeDelay = 3.0f;
	float ExplodeRadius = 300.0f;

	float MaxIntensity = 100000;
	float DeltaLightIntensity = 10000;
	int32 count = 1;

	FTimerHandle LightHandle;

public:
	void Throw(FVector DirectionVec);
	
	UFUNCTION(BlueprintCallable)
	void Explode();
};
