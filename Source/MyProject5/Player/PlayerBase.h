// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"

UENUM()
enum class EHandType : uint8
{
	None = 0,
	MainWeapon,
	SubWeapon,
	Grenade,
	HealPack
};

UCLASS()
class MYPROJECT5_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerBase();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> WeaponComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UParticleSystemComponent> GunShotParticleComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USpotLightComponent> SpotLightComp;
};
