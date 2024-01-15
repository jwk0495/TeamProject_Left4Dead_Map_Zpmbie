// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Player/MyPlayerController.h"
#include "Bullet/Bullet.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Item/ItemBase.h"
#include "Throwable/ThrowableWeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/MainWeapon.h"
#include "Weapon/SubWeapon.h"
#include "public/ZombieBase.h"
#include "Engine/StaticMeshSocket.h"
#include "Particles/ParticleSystemComponent.h"

APlayerCharacter::APlayerCharacter()
{
	// Camera
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->AddRelativeLocation(FVector(30, 0, 70));
	PlayerCamera->bUsePawnControlRotation = true;

	// InputMapping
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/PKH/Input/IMC_FPS.IMC_FPS'"));
	if (MappingContextRef.Object)
	{
		PlayerMappingContext = MappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Move.IA_FPS_Move'"));
	if (MoveActionRef.Object)
	{
		MoveAction = MoveActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Jump.IA_FPS_Jump'"));
	if (JumpActionRef.Object)
	{
		JumpAction = JumpActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Look.IA_FPS_Look'"));
	if (LookActionRef.Object)
	{
		LookAction = LookActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> CrouchActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Crouch.IA_FPS_Crouch'"));
	if (CrouchActionRef.Object)
	{
		CrouchAction = CrouchActionRef.Object;
	}

	// Attack
	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Attack.IA_FPS_Attack'"));
	if (AttackActionRef.Object)
	{
		AttackAction = AttackActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> ReloadActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Reload.IA_FPS_Reload'"));
	if (ReloadActionRef.Object)
	{
		ReloadAction = ReloadActionRef.Object;
	}
	// Hand Change
	static ConstructorHelpers::FObjectFinder<UInputAction> HandChangeToMainActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_HandChangeToMain.IA_FPS_HandChangeToMain'"));
	if (HandChangeToMainActionRef.Object)
	{
		HandChangeToMainAction = HandChangeToMainActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> HandChangeToSubActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_HandChangeToSub.IA_FPS_HandChangeToSub'"));
	if (HandChangeToSubActionRef.Object)
	{
		HandChangeToSubAction = HandChangeToSubActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> HandChangeToGrenadeActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_HandChangeToGrenade.IA_FPS_HandChangeToGrenade'"));
	if (HandChangeToGrenadeActionRef.Object)
	{
		HandChangeToGrenadeAction = HandChangeToGrenadeActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> HandChangeToHealPackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_HandChangeToHealPack.IA_FPS_HandChangeToHealPack'"));
	if (HandChangeToHealPackActionRef.Object)
	{
		HandChangeToHealPackAction = HandChangeToHealPackActionRef.Object;
	}
	// Zoom In/Out
	static ConstructorHelpers::FObjectFinder<UInputAction> ZoomActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Zoom.IA_FPS_Zoom'"));
	if (ZoomActionRef.Object)
	{
		ZoomAction = ZoomActionRef.Object;
	}
	// Heal
	static ConstructorHelpers::FObjectFinder<UInputAction> HealActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Heal.IA_FPS_Heal'"));
	if (HealActionRef.Object)
	{
		HealAction = HealActionRef.Object;
	}
	// MeleeAttack
	static ConstructorHelpers::FObjectFinder<UInputAction> MeleeAttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_MeleeAttack.IA_FPS_MeleeAttack'"));
	if (MeleeAttackActionRef.Object)
	{
		MeleeAttackAction = MeleeAttackActionRef.Object;
	}
	// Get Item
	static ConstructorHelpers::FObjectFinder<UInputAction> GetItemActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_GetItem.IA_FPS_GetItem'"));
	if (GetItemActionRef.Object)
	{
		GetItemAction = GetItemActionRef.Object;
	}

	// Bullet
	static ConstructorHelpers::FClassFinder<ABullet> BulletRef(TEXT("/Game/PKH/BP/BP_Bullet.BP_Bullet_C"));
	if (BulletRef.Class)
	{
		BulletClass = BulletRef.Class;
	}

	//Grenade
	static ConstructorHelpers::FClassFinder<AThrowableWeaponBase> GrenadeRef(TEXT("/Game/PKH/BP/BP_Grenade.BP_Grenade_C"));
	if (GrenadeRef.Class)
	{
		GrenadeClass = GrenadeRef.Class;
	}

	// Weapon Class
	static ConstructorHelpers::FClassFinder<AMainWeapon> MainWeaponRef(TEXT("/Game/PKH/BP/BP_MainWeapon.BP_MainWeapon_C"));
	if (MainWeaponRef.Class)
	{
		MainWeaponClass = MainWeaponRef.Class;
	}
	static ConstructorHelpers::FClassFinder<ASubWeapon> SubWeaponRef(TEXT("/Game/PKH/BP/BP_SubWeapon.BP_SubWeapon_C"));
	if (SubWeaponRef.Class)
	{
		SubWeaponClass = SubWeaponRef.Class;
	}

	// Animation Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ThrowGrenadeMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Animation/AM_Throw.AM_Throw'"));
	if (ThrowGrenadeMontageRef.Object)
	{
		ThrowGrenadeMontage = ThrowGrenadeMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RifleReloadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/AnimationStarter/AM_RifleReload.AM_RifleReload'"));
	if (RifleReloadMontageRef.Object)
	{
		RifleReloadMontage = RifleReloadMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PistolReloadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/AnimationStarter/AM_PistolReload.AM_PistolReload'"));
	if (PistolReloadMontageRef.Object)
	{
		PistolReloadMontage = PistolReloadMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/AnimationStarter/AM_Dead.AM_Dead'"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputCompoennt = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputCompoennt->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputCompoennt->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputCompoennt->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	EnhancedInputCompoennt->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	// Coruch
	EnhancedInputCompoennt->BindAction(CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::CrouchStart);
	EnhancedInputCompoennt->BindAction(CrouchAction, ETriggerEvent::Completed, this, &APlayerCharacter::CrouchEnd);
	// Attack
	EnhancedInputCompoennt->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);
	EnhancedInputCompoennt->BindAction(AttackAction, ETriggerEvent::Completed, this, &APlayerCharacter::AttackEnd);
	EnhancedInputCompoennt->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Reload);
	// HandChange
	EnhancedInputCompoennt->BindAction(HandChangeToMainAction, ETriggerEvent::Started, this, &APlayerCharacter::HandChangeToMain);
	EnhancedInputCompoennt->BindAction(HandChangeToSubAction, ETriggerEvent::Started, this, &APlayerCharacter::HandChangeToSub);
	EnhancedInputCompoennt->BindAction(HandChangeToGrenadeAction, ETriggerEvent::Started, this, &APlayerCharacter::HandChangeToGrenade);
	EnhancedInputCompoennt->BindAction(HandChangeToHealPackAction, ETriggerEvent::Started, this, &APlayerCharacter::HandChangeToHealPack);
	// Zoom In/Out
	EnhancedInputCompoennt->BindAction(ZoomAction, ETriggerEvent::Started, this, &APlayerCharacter::ZoomIn);
	EnhancedInputCompoennt->BindAction(ZoomAction, ETriggerEvent::Completed, this, &APlayerCharacter::ZoomOut);
	// Heal 
	EnhancedInputCompoennt->BindAction(HealAction, ETriggerEvent::Started, this, &APlayerCharacter::Heal);
	// MeleeAttack
	EnhancedInputCompoennt->BindAction(MeleeAttackAction, ETriggerEvent::Started, this, &APlayerCharacter::MeleeAttack);
	// GetItem
	EnhancedInputCompoennt->BindAction(GetItemAction, ETriggerEvent::Started, this, &APlayerCharacter::GetItem);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Mapping
	AMyPlayerController* PlayerController = CastChecked<AMyPlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(PlayerMappingContext, 0);
	}

	PlayerController->InitWidget(this);

	// Status Init
	SetHp(MaxHp);
	SetCurMainAmmo(MaxMainAmmo);
	SetCurSubAmmo(MaxSubAmmo);
	CurShootAccurancy = MaxShootAccurancy;

	// Weapon Actor
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	const FVector HandLocation = GetActorLocation();
	const FRotator HandRotation = FRotator(0, 0, 0);

	MainWeapon = GetWorld()->SpawnActor<AMainWeapon>(MainWeaponClass, HandLocation, HandRotation, Params);
	MainWeapon->SetActorHiddenInGame(true);
	SubWeapon = GetWorld()->SpawnActor<ASubWeapon>(SubWeaponClass, HandLocation, HandRotation, Params);
	SubWeapon->SetActorHiddenInGame(true); 

	// Init WeaponComponent
	CurHand = EHandType::MainWeapon;
	UStaticMesh* MainWeaponMesh = MainWeapon->GetWeaponStaticMesh();
	if (MainWeaponMesh)
	{
		WeaponComponent->SetStaticMesh(MainWeaponMesh);
		WeaponComponent->SetRelativeLocation(MainWeapon->GetWeaponLocation());
		WeaponComponent->SetRelativeScale3D(MainWeapon->GetWeaponScale());
		WeaponComponent->SetRelativeRotation(MainWeapon->GetWeaponRotation());
	}

	GetMyController()->UpdateAmmoUIColor(CurHand);
	GunShotParticleComponent->SetupAttachment(WeaponComponent, TEXT("FireSocket"));
}

AMyPlayerController* APlayerCharacter::GetMyController()
{
	AMyPlayerController* MyController = CastChecked<AMyPlayerController>(GetController());
	return MyController;
}

void APlayerCharacter::Move(const FInputActionValue& InputAction)
{
	FVector2D InputVec = InputAction.Get<FVector2D>();

	const FRotator Rotator = Controller->GetControlRotation();
	const FRotator YawRotator = FRotator(0, Rotator.Yaw, 0);

	const FVector ForwardVec = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	const FVector RightVec = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVec, InputVec.Y);
	AddMovementInput(RightVec, InputVec.X);
}

void APlayerCharacter::Look(const FInputActionValue& InputAction)
{
	if (IsDead)
	{
		return;
	}

	FVector2D InputVec = InputAction.Get<FVector2D>();

	AddControllerPitchInput(InputVec.Y);
	AddControllerYawInput(InputVec.X);
}

void APlayerCharacter::Attack(const FInputActionValue& InputAction)
{
	if (IsMeleeAttackDelay || IsDead)
	{
		return;
	}

	switch (CurHand)
	{
	case EHandType::MainWeapon:
		Shoot();
		break;
	case EHandType::SubWeapon:
		OneShot();
		break;
	case EHandType::Grenade:
		ThrowGrenade();
		break;
	case EHandType::HealPack:

		break;
	}
}

void APlayerCharacter::AttackEnd(const FInputActionValue& InputAction)
{
	if (IsDead)
	{
		return;
	}
	if (CurHand != EHandType::MainWeapon && CurHand != EHandType::SubWeapon)
	{
		return;
	}

	StopShoot();
}

void APlayerCharacter::Reload(const FInputActionValue& InputAction)
{
	if (IsReloading || IsFiring || IsDead)
	{
		return;
	}
	if (CurHand != EHandType::MainWeapon && CurHand != EHandType::SubWeapon)
	{
		return;
	}
	if (CurHand == EHandType::MainWeapon && (CurMainAmmo == MaxMainAmmo || RemainMainAmmo == 0))
	{
		return;
	}
	if (CurHand == EHandType::SubWeapon && CurSubAmmo == MaxSubAmmo)
	{
		return;
	}

	IsReloading = true;

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &APlayerCharacter::ReloadComplete, ReloadDelayTime, false);

	// Animation
	if (CurHand == EHandType::MainWeapon)
	{
		PlayMontage(RifleReloadMontage);
	}
	else
	{
		PlayMontage(PistolReloadMontage);
	}
}

void APlayerCharacter::CrouchStart(const FInputActionValue& InputAction)
{
	IsCrouching = true;
	GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
	GetMesh()->AddRelativeLocation(FVector(0, 0, -40));
	PlayerCamera->AddRelativeLocation(FVector(0, 0, -100));
}

void APlayerCharacter::CrouchEnd(const FInputActionValue& InputAction)
{
	if (IsCrouching == false)
	{
		return;
	}

	IsCrouching = false;
	GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
	GetMesh()->AddRelativeLocation(FVector(0, 0, 40));
	PlayerCamera->AddRelativeLocation(FVector(0, 0, 100));
}

void APlayerCharacter::HandChangeToMain(const FInputActionValue& InputAction)
{
	if (CurHand == EHandType::MainWeapon)
	{
		return;
	}
	if (IsHealing || IsDead)
	{
		return;
	}

	CurHand = EHandType::MainWeapon;
	UStaticMesh* MainWeaponMesh = MainWeapon->GetWeaponStaticMesh();
	if (MainWeaponMesh)
	{
		WeaponComponent->SetStaticMesh(MainWeaponMesh);
		WeaponComponent->SetRelativeLocation(MainWeapon->GetWeaponLocation());
		WeaponComponent->SetRelativeRotation(MainWeapon->GetWeaponRotation());
		WeaponComponent->SetRelativeScale3D(MainWeapon->GetWeaponScale());
	}

	GetMyController()->UpdateAmmoUIColor(CurHand);
	GunShotParticleComponent->SetupAttachment(WeaponComponent, TEXT("FireSocket"));
}

void APlayerCharacter::HandChangeToSub(const FInputActionValue& InputAction)
{
	if (CurHand == EHandType::SubWeapon)
	{
		return;
	}
	if (IsHealing || IsDead)
	{
		return;
	}

	ZoomOut(FInputActionValue());
	CurHand = EHandType::SubWeapon;
	UStaticMesh* SubWeaponMesh = SubWeapon->GetWeaponStaticMesh();
	if (SubWeaponMesh)
	{
		WeaponComponent->SetStaticMesh(SubWeaponMesh);
		WeaponComponent->SetRelativeLocation(SubWeapon->GetWeaponLocation());
		WeaponComponent->SetRelativeRotation(SubWeapon->GetWeaponRotation());
		WeaponComponent->SetRelativeScale3D(SubWeapon->GetWeaponScale());
	}

	GetMyController()->UpdateAmmoUIColor(CurHand);
	GunShotParticleComponent->SetupAttachment(WeaponComponent, TEXT("FireSocket"));
}

void APlayerCharacter::HandChangeToGrenade(const FInputActionValue& InputAction)
{
	if (CurHand == EHandType::Grenade)
	{
		return;
	}
	if (IsHealing || IsDead)
	{
		return;
	}

	ZoomOut(FInputActionValue());
	CurHand = EHandType::Grenade;
	WeaponComponent->SetStaticMesh(nullptr);

	GetMyController()->UpdateAmmoUIColor(CurHand);
}

void APlayerCharacter::HandChangeToHealPack(const FInputActionValue& InputAction)
{
	if (CurHand == EHandType::HealPack)
	{
		return;
	}
	if (IsHealing || IsDead)
	{
		return;
	}

	ZoomOut(FInputActionValue());
	CurHand = EHandType::HealPack;
	WeaponComponent->SetStaticMesh(nullptr);

	GetMyController()->UpdateAmmoUIColor(CurHand);
}

void APlayerCharacter::ZoomIn(const FInputActionValue& InputAction)
{
	if (CurHand != EHandType::MainWeapon)
	{
		return;
	}
	if(IsDead)
	{
		return;
	}

	IsZooming = true;
	PlayerCamera->FieldOfView = ZoomInFov;
	GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
}

void APlayerCharacter::ZoomOut(const FInputActionValue& InputAction)
{
	if (CurHand != EHandType::MainWeapon)
	{
		return;
	}
	if (IsDead)
	{
		return;
	}

	IsZooming = false;
	PlayerCamera->FieldOfView = ZoomOutFov;
	GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
}

void APlayerCharacter::Heal(const FInputActionValue& InputAction)
{
	if (CurHand != EHandType::HealPack || IsHealing || IsDead)
	{
		return;
	}
	if (RemainHealPack < 1)
	{
		return;
	}

	IsHealing = true;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	SetRemainHealPack(RemainHealPack - 1);
	ShowProcessUI();

	PlayerCamera->AddRelativeLocation(FVector(-200, 0, 80));

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda(
		[&]() {
			SetHp(CurHp + HealRate * MaxHp);
			IsHealing = false;
			PlayerCamera->AddRelativeLocation(FVector(200, 0, -80));
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		}), HealDelayTime, false);
}

void APlayerCharacter::MeleeAttack(const FInputActionValue& InputAction)
{
	if (IsMeleeAttackDelay || IsDead)
	{
		return;
	}
	IsMeleeAttackDelay = true;

	if (IsFiring)
	{
		StopShoot();
	}

	const FVector ForwardVec = FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::X);
	FVector AttackCenterVec = GetActorLocation() + MeleeAttackMuzzleOffset + ForwardVec * GetCapsuleComponent()->GetUnscaledCapsuleRadius() * 1.5f;
	
	TArray<FOverlapResult> OverlapResults;
	bool IsHitted = GetWorld()->OverlapMultiByChannel(OverlapResults, AttackCenterVec, FQuat::MakeFromRotator(GetController()->GetControlRotation()),
													  ECollisionChannel::ECC_GameTraceChannel14, FCollisionShape::MakeBox(MeleeAttackBoxVec));

	if (IsHitted)
	{
		for (int i = 0; i < OverlapResults.Num(); i++)
		{
			AZombieBase* Zombie = Cast<AZombieBase>(OverlapResults[i].GetActor());
			if (Zombie)
			{
				FVector MyLocation = GetActorLocation();
				MyLocation.Z = 0;
				FVector TargetLocation = Zombie->GetActorLocation();
				TargetLocation.Z = 0;
				FVector DirectionVec = TargetLocation - MyLocation;
				DirectionVec.Normalize();
				Zombie->LaunchCharacter(DirectionVec * KnuckbackPower, true, false);

				Zombie->OnKnuckback();
				Zombie->OnDamaged(MeleeAttackPower);
				UE_LOG(LogTemp, Log, TEXT("Melee Attack Hit: %d"), MeleeAttackPower);
			}
		}
	}

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda(
		[&]() {
			IsMeleeAttackDelay = false;
		}), MeleeAttackDelay, false);
}

void APlayerCharacter::GetItem(const FInputActionValue& InputAction)
{
	if (IsDead || NearbyItem == nullptr)
	{
		return;
	}

	FItemData ItemData = NearbyItem->GetItemData();
	switch (ItemData.ItemType)
	{
	case EItemType::Heal:
		SetRemainHealPack(RemainHealPack + ItemData.ItemValue);
		break;
	case EItemType::Ammo:
		SetRemainMainAmmo(RemainMainAmmo + ItemData.ItemValue);
		break;
	case EItemType::Grenade:
		SetRemainGrenade(RemainGrenade + ItemData.ItemValue);
		break;
	}
	NearbyItem->Destroy();
	RemoveNearbyItem(NearbyItem);
}

float APlayerCharacter::GetMoveSpeed() const
{
	if (IsCrouching)
	{
		return MoveSpeedInCrouch;
	}
	if (IsZooming)
	{
		return MoveSpeedInZooming;
	}

	return IsFiring ? MoveSpeedInFiring : MoveSpeedInNormal;
}

int APlayerCharacter::SetHp(int32 NewHp)
{
	CurHp = FMath::Clamp(NewHp, 0, MaxHp);
	OnHpChanged.ExecuteIfBound((float)CurHp / MaxHp);
	if (CurHp == 0)
	{
		OnDie();
	}

	return CurHp;
}

int APlayerCharacter::SetCurMainAmmo(int32 NewCurAmmo)
{
	CurMainAmmo = FMath::Clamp(NewCurAmmo, 0, MaxMainAmmo);
	OnMainAmmoChanged.ExecuteIfBound(CurMainAmmo, RemainMainAmmo);

	if (CurMainAmmo == 0)
	{
		StopShoot();
	}

	return CurMainAmmo;
}

int APlayerCharacter::SetRemainMainAmmo(int32 NewRemainAmmo)
{
	RemainMainAmmo = FMath::Clamp(NewRemainAmmo, 0, 500); // 500 is temp
	OnMainAmmoChanged.ExecuteIfBound(CurMainAmmo, RemainMainAmmo);

	return RemainMainAmmo;
}

int APlayerCharacter::SetCurSubAmmo(int32 NewCurAmmo)
{
	CurSubAmmo = FMath::Clamp(NewCurAmmo, 0, MaxSubAmmo);
	OnSubAmmoChanged.ExecuteIfBound(CurSubAmmo);

	return CurSubAmmo;
}

int APlayerCharacter::SetRemainGrenade(int32 NewRemainGrenade)
{
	RemainGrenade = FMath::Clamp(NewRemainGrenade, 0, 500); // 500 is temp
	OnGrenadeChanged.ExecuteIfBound(RemainGrenade);

	return RemainGrenade;
}

int APlayerCharacter::SetRemainHealPack(int32 NewRemainHealPack)
{
	RemainHealPack = FMath::Clamp(NewRemainHealPack, 0, 500); // 500 is temp
	OnHealPackChanged.ExecuteIfBound(RemainHealPack);

	return RemainHealPack;
}

void APlayerCharacter::OnDamaged(int32 InDamage)
{
	if (IsDead)
	{
		return;
	}

	SetHp(CurHp - InDamage);
	UE_LOG(LogTemp, Log, TEXT("OnDamaged: %d"), InDamage);
}

void APlayerCharacter::OnDie()
{
	IsDead = true;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	StopShoot();

	// Animation
	PlayMontage(DeadMontage);

	// GameOver UI
	GetMyController()->GameOver();
}

void APlayerCharacter::ShowProcessUI()
{
	if (IsReloading)
	{
		GetMyController()->ShowProcessUI(FText::FromString(TEXT("Reloading...")), ReloadDelayTime);
	}
	else if (IsHealing)
	{
		GetMyController()->ShowProcessUI(FText::FromString(TEXT("Healing...")), HealDelayTime);
	}
}

void APlayerCharacter::PlayMontage(UAnimMontage* NewMontage)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(NewMontage);
}

void APlayerCharacter::SetShootAccurancy(float NewShootAccurancy)
{
	CurShootAccurancy = FMath::Clamp(NewShootAccurancy, 0.0f, MaxShootAccurancy);
	OnShootAccurancyChanged.ExecuteIfBound(CurShootAccurancy);
}

float APlayerCharacter::GetShootDeltaAccurancy() const
{
	float DeltaAccurancy = 0;
	if (CurHand == EHandType::MainWeapon)
	{
		DeltaAccurancy = DeltaShootAccurancyMainWeapon;
	}
	else if (CurHand == EHandType::SubWeapon)
	{
		DeltaAccurancy = DeltaShootAccurancySubweapon;
	}

	return IsZooming || IsCrouching ? DeltaAccurancy * DeltaShootAccurancyRateInZoom : DeltaAccurancy;
}

int32 APlayerCharacter::GetAttackPower()
{
	if (CurHand == EHandType::MainWeapon)
	{
		return MainWeapon->GetAttackPower();
	}
	else if (CurHand == EHandType::SubWeapon)
	{
		return SubWeapon->GetAttackPower();
	}

	return 0;
}

void APlayerCharacter::OneShot()
{
	if (CurHand == EHandType::MainWeapon && CurMainAmmo < 1)
	{
		return;
	}
	if (CurHand == EHandType::SubWeapon && CurSubAmmo < 1)
	{
		return;
	}
	
	FVector FireSocketLocation = WeaponComponent->GetSocketLocation(TEXT("FireSocket")); 
	FRotator FireSocketRotator = WeaponComponent->GetSocketRotation(TEXT("FireSocket"));

	const FVector MuzzleLocation = FireSocketLocation;
	const FRotator MuzzleRotator = FireSocketRotator;

	const FRotator ControllerRotator = FireSocketRotator;
	const FVector FireSocketForwardVec = FRotationMatrix(ControllerRotator).GetUnitAxis(EAxis::X);
	const FVector FireSocketRightVec = FRotationMatrix(ControllerRotator).GetUnitAxis(EAxis::Y);
	const FVector FireSocketUpVec = FRotationMatrix(ControllerRotator).GetUnitAxis(EAxis::Z);

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	FVector FireDirectionVec = FireSocketForwardVec;

	float XOffset = FMath::RandRange(-1, 1) > 0 ? (1 - CurShootAccurancy) : -(1 - CurShootAccurancy);
	float YOffset = FMath::RandRange(-1, 1) > 0 ? (1 - CurShootAccurancy) : -(1 - CurShootAccurancy);
	FireDirectionVec = FireDirectionVec.RotateAngleAxis(XOffset * ShootAccurancyValue, FireSocketRightVec);
	FireDirectionVec = FireDirectionVec.RotateAngleAxis(YOffset * ShootAccurancyValue, FireSocketUpVec);
	
	ABullet* Projectile = GetWorld()->SpawnActor<ABullet>(BulletClass, MuzzleLocation, MuzzleRotator, Params);
	if (Projectile)
	{
		Projectile->Fire(FireDirectionVec, GetAttackPower());
	}

	if (CurHand == EHandType::MainWeapon)
	{
		SetCurMainAmmo(CurMainAmmo - 1);;
	}
	else
	{
		SetCurSubAmmo(CurSubAmmo - 1);;
	}

	// Accurancy
	SetShootAccurancy(CurShootAccurancy - GetShootDeltaAccurancy());

	// recoil 
	FVector RecoilVec = FVector::DownVector + FVector(FMath::RandRange(-1.0f, 1.0f), 0, 0);
	RecoilVec.Normalize();
	RecoilVec = IsZooming ? RecoilVec * RecoilOffsetInZoom : RecoilVec * RecoilOffsetInNormal;

	AddControllerPitchInput(RecoilVec.Z);
	AddControllerYawInput(RecoilVec.X);

	// Particle
	//GunShotParticleComponent->SetActive(true);
}

void APlayerCharacter::Shoot()
{
	if (IsReloading)
	{
		return;
	}

	if (false == IsFiring)
	{
		OneShot();

		IsFiring = true;
		GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
		
		if (!FireHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(FireHandle,
				FTimerDelegate::CreateLambda([this]()
					{
						OneShot();
						// Fire Start
						if (CurMainAmmo < 1)
						{
							this->IsFiring = false;
							GetWorld()->GetTimerManager().ClearTimer(FireHandle);
						}
					}), FireDelayTime, true);
		}
	}
}

void APlayerCharacter::StopShoot()
{
	IsFiring = false;
	GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
	
	if (FireHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(FireHandle);
	}

	// Accurancy
	GetWorld()->GetTimerManager().SetTimer(AccurancyHandle, FTimerDelegate::CreateLambda(
		[&]() {
			SetShootAccurancy(CurShootAccurancy + DeltaShootAccurancyRecovery);
			if (CurShootAccurancy == MaxShootAccurancy)
				GetWorld()->GetTimerManager().ClearTimer(AccurancyHandle);
		}), 0.05f, true);
}

void APlayerCharacter::ReloadComplete()
{
	if (CurHand == EHandType::MainWeapon)
	{
		int32 diff = MaxMainAmmo - CurMainAmmo;
		if (diff >= RemainMainAmmo)
		{
			SetCurMainAmmo(CurMainAmmo + RemainMainAmmo);
			SetRemainMainAmmo(0);
		}
		else
		{
			SetCurMainAmmo(MaxMainAmmo);
			SetRemainMainAmmo(RemainMainAmmo - diff);
		}
	}
	else if (CurHand == EHandType::SubWeapon)
	{
		SetCurSubAmmo(MaxSubAmmo);
	}
	IsReloading = false;

	UE_LOG(LogTemp, Log, TEXT("%d / %d"), CurMainAmmo, RemainMainAmmo);
}

void APlayerCharacter::ThrowGrenade()
{
	if (RemainGrenade < 1 || IsThrowing)
	{
		return;
	}
	IsThrowing = true;

	const FVector MuzzleLocation = GetActorLocation() + FVector(0, 0, GetMuzzleOffsetZ()) + (GetActorForwardVector() * (GetCapsuleComponent()->GetUnscaledCapsuleRadius()));
	const FRotator MuzzleRotator = FRotationMatrix::MakeFromX(GetActorForwardVector()).Rotator();

	const FRotator ControllerRotator = Controller->GetControlRotation();
	const FVector ControllerForwardVec = FRotationMatrix(ControllerRotator).GetUnitAxis(EAxis::X);
	const FVector ControllerUpVec = FRotationMatrix(ControllerRotator).GetUnitAxis(EAxis::Z) * 0.2f;
	FVector ThrowDirVec = (ControllerForwardVec + ControllerUpVec);
	ThrowDirVec.Normalize();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	AThrowableWeaponBase* Throwable = GetWorld()->SpawnActor<AThrowableWeaponBase>(GrenadeClass, MuzzleLocation, MuzzleRotator, Params);
	if (Throwable)
	{
		Throwable->Throw(ThrowDirVec);
	}
	SetRemainGrenade(RemainGrenade - 1);
	UE_LOG(LogTemp, Log, TEXT("Grenade: %d"), RemainGrenade);

	// Timer
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle,
		[&]()
		{
			IsThrowing = false;
		}, 1.0f, false, ThrowDelay);

	// Animation
	PlayMontage(ThrowGrenadeMontage);
}

void APlayerCharacter::SetNearbyItem(AItemBase* InItem)
{
	NearbyItem = InItem;
	FText ItemText = FText::FromString(FString::Printf(TEXT("%s 획득하기"), *NearbyItem->GetItemData().ItemText));
	OnNearbyItemChanged.ExecuteIfBound(true, ItemText);
}

void APlayerCharacter::RemoveNearbyItem(AItemBase* OutItem)
{
	if (NearbyItem != OutItem)
	{
		return;
	}
	NearbyItem = nullptr;
	OnNearbyItemChanged.ExecuteIfBound(false, FText());
}
