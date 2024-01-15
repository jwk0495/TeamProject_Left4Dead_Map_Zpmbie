// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class MYPROJECT5_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackPower = 0;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> WeaponMeshComponent;

	UPROPERTY(EditAnywhere)
	FVector WeaponLocation;

	UPROPERTY(EditAnywhere)
	FVector WeaponScale;

	UPROPERTY(EditAnywhere)
	FRotator WeaponRotation;

public:
	FORCEINLINE int32 GetAttackPower() const { return AttackPower; }
	
	FORCEINLINE FVector GetWeaponLocation() const { return WeaponLocation; }
	FORCEINLINE FRotator GetWeaponRotation() const { return WeaponRotation; }
	FORCEINLINE FVector GetWeaponScale() const { return WeaponScale; }

	class UStaticMesh* GetWeaponStaticMesh();
};
