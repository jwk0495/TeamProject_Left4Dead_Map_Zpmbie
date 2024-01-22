// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerBase.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FOnHpChangedDelegate, float /*InHpRate*/);
DECLARE_DELEGATE_TwoParams(FOnMainAmmoChangedDelegate, int /*InCurAmmo*/, int /*RemainAmmo*/);
DECLARE_DELEGATE_OneParam(FOnSubAmmoChangedDelegate, int /*InCurAmmo*/);
DECLARE_DELEGATE_OneParam(FOnGrenadeChangedDelegate, int /*RemainGrenade*/);
DECLARE_DELEGATE_OneParam(FOnHealPackChangedDelegate, int /*RemainHealPack*/);
DECLARE_DELEGATE_OneParam(FOnShootAccurancyChangedDelegate, float /*ShootAccurancy*/);
DECLARE_DELEGATE_TwoParams(FOnNearbyItemChangedDelegate, bool /*IsExist*/, FText /*NewItemText*/);
DECLARE_DELEGATE_OneParam(FOnPlayerDamagedDelegate, bool /*IsDead*/);

/**
 * 
 */

UCLASS()
class MYPROJECT5_API APlayerCharacter : public APlayerBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float Deltatime) override;

	class AMyPlayerController* GetMyController();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCameraComponent> PlayerCamera;

// Input Action
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputMappingContext> PlayerMappingContext;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> CrouchAction;

	// Attack
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> ReloadAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> ZoomAction;

	// Hand Change
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> HandChangeToMainAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> HandChangeToSubAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> HandChangeToGrenadeAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> HandChangeToHealPackAction;

	// Heal
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> HealAction;

	// Heal
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> MeleeAttackAction;

	// Get Item
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> GetItemAction;


	void Move(const FInputActionValue& InputAction);
	void Look(const FInputActionValue& InputAction);

	void Attack(const FInputActionValue& InputAction);
	void AttackEnd(const FInputActionValue& InputAction);
	void Reload(const FInputActionValue& InputAction);

	void CrouchStart(const FInputActionValue& InputAction);
	void CrouchEnd(const FInputActionValue& InputAction);

	void HandChangeToMain(const FInputActionValue& InputAction);
	void HandChangeToSub(const FInputActionValue& InputAction);
	void HandChangeToGrenade(const FInputActionValue& InputAction);
	void HandChangeToHealPack(const FInputActionValue& InputAction);

	void ZoomIn(const FInputActionValue& InputAction);
	void ZoomOut(const FInputActionValue& InputAction);

	void Heal(const FInputActionValue& InputAction);

public:
	void HealEnd();

protected:
	void MeleeAttack(const FInputActionValue& InputAction);

	void GetItem(const FInputActionValue& InputAction);

// Move
protected:
	bool IsCrouching = false;
	float MoveSpeedInNormal = 500.0f;
	float MoveSpeedInFiring = 350.0f;
	float MoveSpeedInZooming = 200.0f;
	float MoveSpeedInCrouch = 150.0f;

	float GetMoveSpeed() const;

// Weapon
protected:
	UPROPERTY()
	TSubclassOf<class AMainWeapon> MainWeaponClass;

	UPROPERTY()
	TObjectPtr<class AMainWeapon> MainWeapon;

	UPROPERTY()
	TSubclassOf<class ASubWeapon> SubWeaponClass;

	UPROPERTY()
	TObjectPtr<class ASubWeapon> SubWeapon;

	UPROPERTY()
	TSubclassOf<class AGrenadeHand> GrenadeHandClass;

	UPROPERTY()
	TObjectPtr<class AGrenadeHand> GrenadeHand;

	UPROPERTY()
	TSubclassOf<class AHealPackHand> HealPackHandClass;

	UPROPERTY()
	TObjectPtr<class AHealPackHand> HealPackHand;

// HandType
protected:
	EHandType CurHand = EHandType::MainWeapon;

// Shoot & Reload
protected:
	UPROPERTY()
	TSubclassOf<class ABullet> BulletClass;

	FTimerHandle FireHandle;
	FTimerHandle AccurancyHandle;

	bool IsReloading = false;
	bool IsFiring = false;
	bool IsZooming = false;
	float FireDelayTime = 0.12f;
	float MuzzleOffsetZInNormal = 70.0f;
	float MuzzleOffsetZInCrouch = 35.0f;

	UPROPERTY(EditAnywhere)
	float ReloadDelayTime = 1.5f;

	float ZoomInFov = 60.0f;
	float ZoomOutFov = 90.0f;

	// Shoot Accurancy
	float CurShootAccurancy = 1.0f;
	float MaxShootAccurancy = 1.0f;
	float DeltaShootAccurancyMainWeapon = 0.01f;
	float DeltaShootAccurancySubweapon = 0.05f;
	float DeltaShootAccurancyRateInZoom = 0.5f;
	float DeltaShootAccurancyRecovery = 0.025f;
	float ShootAccurancyValue = 5.0f;

	void SetShootAccurancy(float NewShootAccurancy);

	FORCEINLINE float GetMuzzleOffsetZ() const { return IsCrouching ? MuzzleOffsetZInCrouch : MuzzleOffsetZInNormal; }
	float GetShootDeltaAccurancy() const;

	int32 GetAttackPower();

	void OneShot();
	void Shoot();
	void StopShoot();

public:
	void ReloadComplete();

public:
	FORCEINLINE uint8 GetIsDead() const { return IsDead; }
	FORCEINLINE uint8 GetIsFiring() const { return IsFiring; }
	FORCEINLINE uint8 GetIsClear() const { return IsClear; }
	FORCEINLINE uint8 GetIsCrouching() const { return IsCrouching; }

	FORCEINLINE uint8 GetIsMainWeapon() const { return CurHand == EHandType::MainWeapon; }
	FORCEINLINE uint8 GetIsSubWeapon() const { return CurHand == EHandType::SubWeapon; }
	FORCEINLINE uint8 GetIsGrenade() const { return CurHand == EHandType::Grenade; }
	FORCEINLINE uint8 GetIsHealPack() const { return CurHand == EHandType::HealPack; }
	

// Recoil
protected:
	float RecoilOffsetInNormal = 0.4f;
	float RecoilOffsetInZoom = 0.2f;
	
// Grenade
protected:
	UPROPERTY()
	TSubclassOf<class AThrowableWeaponBase> GrenadeClass;

	bool IsThrowing = false; 

public:
	void ThrowBegin();
	void ThrowGrenade();
	void ThrowEnd();

// HealPack
protected:
	bool IsHealing = false;
	float HealDelayTime = 4.0f;
	float HealRate = 0.6f;

// Melee Attack
protected:
	FVector MeleeAttackBoxVec = FVector(50, 80, 35);
	FVector MeleeAttackMuzzleOffset = FVector(0, 0, 30);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MeleeAttackPower = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnuckbackPower = 150.0f;

	bool IsMeleeAttackDelay = false;
	float MeleeAttackDelay = 0.6f;

public:
	void MeleeAttackHit();
	void MeleeAttackEnd();

// Nearby Item
protected:
	UPROPERTY()
	TObjectPtr<class AItemBase> NearbyItem;

public:
	void SetNearbyItem(class AItemBase* InItem);
	void RemoveNearbyItem(class AItemBase* OutItem);

public:
	void GameClear();

// Status
protected:
	UPROPERTY(EditAnywhere)
	int32 MaxHp = 100;

	UPROPERTY(EditAnywhere)
	int32 CurHp = 0;

	UPROPERTY(EditAnywhere)
	int32 CurMainAmmo = 50;

	int32 MaxMainAmmo = 50;

	UPROPERTY(EditAnywhere)
	int32 CurRemainMainAmmo = 250;

	UPROPERTY(EditAnywhere)
	int32 MaxRemainMainAmmo = 250;

	UPROPERTY(EditAnywhere)
	int32 CurSubAmmo = 12;

	int32 MaxSubAmmo = 12;

	UPROPERTY(EditAnywhere)
	int32 RemainGrenade = 1;

	UPROPERTY(EditAnywhere)
	int32 RemainHealPack = 1;

	bool IsDead = false;
	bool IsClear = false;

public:
	UFUNCTION()
	int SetHp(int32 NewHp);

	void OnDie();

	UFUNCTION()
	int SetCurMainAmmo(int32 NewCurAmmo);

	UFUNCTION()
	int SetRemainMainAmmo(int32 NewRemainAmmo);

	UFUNCTION()
	int SetCurSubAmmo(int32 NewCurAmmo);

	UFUNCTION()
	int SetRemainGrenade(int32 NewRemainGrenade);

	UFUNCTION()
	int SetRemainHealPack(int32 NewRemainHealPack);

	UFUNCTION(BlueprintCallable)
	void OnDamaged(int32 InDamage);
	
// Delegate
public:
	FOnHpChangedDelegate OnHpChanged;
	FOnMainAmmoChangedDelegate OnMainAmmoChanged;
	FOnSubAmmoChangedDelegate OnSubAmmoChanged;
	FOnGrenadeChangedDelegate OnGrenadeChanged;
	FOnHealPackChangedDelegate OnHealPackChanged;
	FOnShootAccurancyChangedDelegate OnShootAccurancyChanged;
	FOnNearbyItemChangedDelegate OnNearbyItemChanged;
	FOnPlayerDamagedDelegate OnPlayerDamaged;

protected:
	void ShowProcessUI();


// Animation
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> ThrowGrenadeMontage;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> RifleReloadMontage;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> PistolReloadMontage;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> MeleeAttackMontage;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> HealMontage;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimMontage> DeadMontage;

	void PlayMontage(class UAnimMontage* NewMontage);

// Sound
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class USoundBase>> SFX_OnDamaged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class USoundBase>> SFX_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USoundBase> SFX_Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USoundBase> SFX_LowHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USoundBase> SFX_RifleFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USoundBase> SFX_PistolFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USoundBase> SFX_Explosion;

	// LowHealth
	FTimerHandle LowHealthHandle;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> LowHealthComp;
};
