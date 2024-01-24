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
	TObjectPtr<class USoundAttenuation> SoundSetting;

	UPROPERTY(EditAnywhere)
	int32 AttackPower = 0;

	float ExplodeDelay = 3.0f;
	float ExplodeRadius = 400.0f;

	float MaxIntensity = 100000;
	float DeltaLightIntensity = 10000;
	int32 count = 1;

	FTimerHandle LightHandle;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> ShakeClass;

	float InnerShakeRadius = 1500.0f;
	float OuterShakeRadius = 3000.0f;

public:
	void Throw(FVector DirectionVec);
	
	UFUNCTION(BlueprintCallable)
	void Explode();

// Sound
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USoundBase> SFX_Explosion;
};
