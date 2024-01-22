// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HelicopterPawn.generated.h"

UCLASS()
class MYPROJECT5_API AHelicopterPawn : public APawn
{
	GENERATED_BODY()

public:
	AHelicopterPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UCameraComponent> HelicopterCamera;

	FVector LandLocation = FVector(342, 106, 1880);
	FVector DestLocation = FVector(5112, 106, 6323);
	float LandAlpha = 0;
	float DestAlpha = 0;
	bool IsLanded = false;

};
