// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombieBase.generated.h"

UCLASS()
class MYPROJECT5_API AZombieBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackPower;

	// Functions
public:
	UFUNCTION(BlueprintCallable)
	void OnDamaged(int32 InDamage);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDie();

};
