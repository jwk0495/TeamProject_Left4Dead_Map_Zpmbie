// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UENUM()
enum class EItemType: uint8
{
	None = 0,
	Heal,
	Ammo,
	Grenade
};

USTRUCT()
struct FItemData
{
	GENERATED_USTRUCT_BODY()

public:
	FItemData() : ItemType(EItemType::None), ItemValue(0), ItemText(TEXT("")) {}
	FItemData(EItemType Type, int32 Value, FString Text) : ItemType(Type), ItemValue(Value), ItemText(Text) {}

	EItemType ItemType;
	int32 ItemValue;
	FString ItemText;
};

UCLASS()
class MYPROJECT5_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

	FORCEINLINE FItemData GetItemData() const { return ItemData; };

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UMaterialInterface> OverlayMaterial;

	FItemData ItemData;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE void OutlineOff() { Mesh->SetOverlayMaterial(nullptr); }
};
