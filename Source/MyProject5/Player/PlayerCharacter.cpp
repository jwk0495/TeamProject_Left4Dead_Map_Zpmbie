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
#include "Weapon/GrenadeHand.h"
#include "Weapon/HealPackHand.h"
#include "public/ZombieBase.h"
#include "Engine/StaticMeshSocket.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Props/HelicopterPawn.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

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
	static ConstructorHelpers::FClassFinder<AGrenadeHand> GrenadeHandRef(TEXT("/Game/PKH/BP/BP_GrenadeHand.BP_GrenadeHand_C"));
	if (GrenadeHandRef.Class)
	{
		GrenadeHandClass = GrenadeHandRef.Class;
	}
	static ConstructorHelpers::FClassFinder<AHealPackHand> HealPackHandRef(TEXT("/Game/PKH/BP/BP_HealPackHand.BP_HealPackHand_C"));
	if (HealPackHandRef.Class)
	{
		HealPackHandClass = HealPackHandRef.Class;
	}


	// Animation Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ThrowGrenadeMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/AnimationStarter/AM_ThrowGrenade.AM_ThrowGrenade'"));
	if (ThrowGrenadeMontageRef.Object)
	{
		ThrowGrenadeMontage = ThrowGrenadeMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RifleReloadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/AnimationStarter/AM_RifleReloading.AM_RifleReloading'"));
	if (RifleReloadMontageRef.Object)
	{
		RifleReloadMontage = RifleReloadMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PistolReloadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/AnimationStarter/AM_PistolReload.AM_PistolReload'"));
	if (PistolReloadMontageRef.Object)
	{
		PistolReloadMontage = PistolReloadMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MeleeAttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/AnimationStarter/AM_MeleeAttack.AM_MeleeAttack'"));
	if (MeleeAttackMontageRef.Object)
	{
		MeleeAttackMontage = MeleeAttackMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HealMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/AnimationStarter/AM_Heal.AM_Heal'"));
	if (HealMontageRef.Object)
	{
		HealMontage = HealMontageRef.Object;
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
	// Crouch
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
	SetRemainGrenade(1);
	SetRemainHealPack(1);
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
	GrenadeHand = GetWorld()->SpawnActor<AGrenadeHand>(GrenadeHandClass, HandLocation, HandRotation, Params);
	GrenadeHand->SetActorHiddenInGame(true);
	HealPackHand = GetWorld()->SpawnActor<AHealPackHand>(HealPackHandClass, HandLocation, HandRotation, Params);
	HealPackHand->SetActorHiddenInGame(true);

	// Init WeaponComponent
	CurHand = EHandType::MainWeapon;
	UStaticMesh* MainWeaponMesh = MainWeapon->GetWeaponStaticMesh();
	if (MainWeaponMesh)
	{
		WeaponComponent->SetStaticMesh(MainWeaponMesh);
		WeaponComponent->SetRelativeLocation(MainWeapon->GetWeaponLocation());
		WeaponComponent->SetRelativeRotation(MainWeapon->GetWeaponRotation());
		WeaponComponent->SetWorldScale3D(MainWeapon->GetWeaponScale());
	}

	GetMyController()->UpdateAmmoUIColor(CurHand);
	GunShotParticleComponent->SetupAttachment(WeaponComponent, TEXT("FireSocket"));
	GunShotParticleComponent->SetRelativeScale3D(FVector(0.03f));

	// Sound
	LowHealthComp = UGameplayStatics::SpawnSound2D(GetWorld(), SFX_LowHealth);
	LowHealthComp->Stop();
	LowHealthComp->bAutoDestroy = false;

	BgmComp = UGameplayStatics::SpawnSound2D(GetWorld(), BGM_Normal);
	BgmComp->bAutoDestroy = false;

	// Announce
	InitialCameraLocation = PlayerCamera->GetComponentLocation();
	PlayerCamera->AddRelativeLocation(FVector(-5000, 0, 4000));
	AddControllerPitchInput(10);
	GetCharacterMovement()->SetMovementMode(MOVE_None);

	FTimerHandle AnnounceHandle;
	GetWorldTimerManager().SetTimer(AnnounceHandle, FTimerDelegate::CreateLambda(
		[&]() {
			IsAnnouncing = true;
		}), 1.5f, false);
}

void APlayerCharacter::Tick(float Deltatime)
{
	if (IsAnnouncing)
	{
		PlayerCamera->SetWorldLocation(FMath::VInterpTo(PlayerCamera->GetComponentLocation(), DestinationLocation, Deltatime, 0.4f));
		if (FVector::Distance(PlayerCamera->GetComponentLocation(), DestinationLocation) < 800.0f)
		{
			IsAnnouncing = false;
			PlayerCamera->SetWorldLocation(InitialCameraLocation);
			AddControllerPitchInput(-10);
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);

			GetMyController()->EndAnnounce();
			UGameplayStatics::PlaySound2D(GetWorld(), SFX_Start);
		}
	}
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
	if (IsDead || IsAnnouncing)
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
		ThrowBegin();
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
	if (IsReloading || IsFiring || IsMeleeAttackDelay || IsDead)
	{
		return;
	}
	if (CurHand != EHandType::MainWeapon && CurHand != EHandType::SubWeapon)
	{
		return;
	}
	if (CurHand == EHandType::MainWeapon && (CurMainAmmo == MaxMainAmmo || CurRemainMainAmmo == 0))
	{
		return;
	}
	if (CurHand == EHandType::SubWeapon && CurSubAmmo == MaxSubAmmo)
	{
		return;
	}

	IsReloading = true;

	// Animation
	if (CurHand == EHandType::MainWeapon)
	{
		PlayMontage(RifleReloadMontage);
		UGameplayStatics::PlaySound2D(GetWorld(), SFX_ReloadRifle);
	}
	else
	{
		PlayMontage(PistolReloadMontage);
		UGameplayStatics::PlaySound2D(GetWorld(), SFX_ReloadPistol);
	}

	// Sound
	USoundBase* ReloadSound = SFX_Reload[FMath::RandRange(0, SFX_Reload.Num() - 1)];
	UGameplayStatics::PlaySound2D(GetWorld(), ReloadSound);
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

	IsReloading = false;
	IsThrowing = false;

	CurHand = EHandType::MainWeapon;
	UStaticMesh* MainWeaponMesh = MainWeapon->GetWeaponStaticMesh();
	if (MainWeaponMesh)
	{
		WeaponComponent->SetStaticMesh(MainWeaponMesh);
		WeaponComponent->SetRelativeLocation(MainWeapon->GetWeaponLocation());
		WeaponComponent->SetRelativeRotation(MainWeapon->GetWeaponRotation());
		WeaponComponent->SetWorldScale3D(MainWeapon->GetWeaponScale());
	}

	GetMyController()->UpdateAmmoUIColor(CurHand);
	GunShotParticleComponent->SetupAttachment(WeaponComponent, TEXT("FireSocket"));
	GunShotParticleComponent->SetRelativeScale3D(FVector(0.03f, 0.03f, 0.03f));

	// Sound
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_ChangeToRifle);
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

	IsReloading = false;
	IsThrowing = false;

	ZoomOut(FInputActionValue());
	CurHand = EHandType::SubWeapon;
	UStaticMesh* SubWeaponMesh = SubWeapon->GetWeaponStaticMesh();
	if (SubWeaponMesh)
	{
		WeaponComponent->SetStaticMesh(SubWeaponMesh);
		WeaponComponent->SetRelativeLocation(SubWeapon->GetWeaponLocation());
		WeaponComponent->SetRelativeRotation(SubWeapon->GetWeaponRotation());
		WeaponComponent->SetWorldScale3D(SubWeapon->GetWeaponScale());
	}

	GetMyController()->UpdateAmmoUIColor(CurHand);
	GunShotParticleComponent->SetupAttachment(WeaponComponent, TEXT("FireSocket"));
	GunShotParticleComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));

	// Sound
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_ChangeToPistol);
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

	IsReloading = false;
	IsThrowing = false;

	ZoomOut(FInputActionValue());
	CurHand = EHandType::Grenade;
	if (RemainGrenade > 0)
	{
		UStaticMesh* GrenadeHandMesh = GrenadeHand->GetWeaponStaticMesh();
		if (GrenadeHandMesh)
		{
			WeaponComponent->SetStaticMesh(GrenadeHandMesh);
			WeaponComponent->SetRelativeLocation(GrenadeHand->GetWeaponLocation());
			WeaponComponent->SetRelativeRotation(GrenadeHand->GetWeaponRotation());
			WeaponComponent->SetWorldScale3D(GrenadeHand->GetWeaponScale());
		}
	}
	else
	{
		WeaponComponent->SetStaticMesh(nullptr);
	}
	

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

	IsReloading = false;
	IsThrowing = false;

	ZoomOut(FInputActionValue());
	CurHand = EHandType::HealPack;
	if (RemainHealPack > 0)
	{
		UStaticMesh* HealPackHandMesh = HealPackHand->GetWeaponStaticMesh();
		if (HealPackHandMesh)
		{
			WeaponComponent->SetStaticMesh(HealPackHandMesh);
			WeaponComponent->SetRelativeLocation(HealPackHand->GetWeaponLocation());
			WeaponComponent->SetRelativeRotation(HealPackHand->GetWeaponRotation());
			WeaponComponent->SetWorldScale3D(HealPackHand->GetWeaponScale());
		}
	}
	else
	{
		WeaponComponent->SetStaticMesh(nullptr);
	}
	

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

	if (IsReloading)
	{
		IsReloading = false;
	}

	IsHealing = true;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	SetRemainHealPack(RemainHealPack - 1);

	ShowProcessUI();

	PlayerCamera->AddRelativeLocation(FVector(-200, 0, 80));
	bUseControllerRotationYaw = false;
	WeaponComponent->SetStaticMesh(nullptr);

	PlayMontage(HealMontage);
}

void APlayerCharacter::HealEnd()
{
	SetHp(CurHp + HealRate * MaxHp);
	IsHealing = false;
	PlayerCamera->AddRelativeLocation(FVector(200, 0, -80));
	bUseControllerRotationYaw = true;

	if (RemainHealPack > 0)
	{
		WeaponComponent->SetStaticMesh(HealPackHand->GetWeaponStaticMesh());
	}
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void APlayerCharacter::MeleeAttack(const FInputActionValue& InputAction)
{
	if (IsMeleeAttackDelay || IsHealing || IsDead)
	{
		return;
	}
	IsMeleeAttackDelay = true;

	if (IsFiring)
	{
		StopShoot();
	}

	if (IsReloading)
	{
		IsReloading = false;
	}

	PlayMontage(MeleeAttackMontage);
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
		if (CurRemainMainAmmo < MaxRemainMainAmmo)
		{
			SetRemainMainAmmo(CurRemainMainAmmo + ItemData.ItemValue);
		}
		break;
	case EItemType::Grenade:
		SetRemainGrenade(RemainGrenade + ItemData.ItemValue);
		break;
	}

	if (ItemData.ItemType != EItemType::Ammo)
	{
		NearbyItem->Destroy();
		RemoveNearbyItem(NearbyItem);
	}
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
	float HpRate = (float)CurHp / MaxHp;
	OnHpChanged.ExecuteIfBound(HpRate);
	if (CurHp == 0)
	{
		OnDie();
	}
	else
	{
		if (HpRate <= 0.3f && false == LowHealthHandle.IsValid())
		{
			GetMyController()->SetLowHealthFilter(true);
			LowHealthComp->Play();
			GetWorldTimerManager().SetTimer(LowHealthHandle, FTimerDelegate::CreateLambda( [&]() { LowHealthComp->Play(); }), 5.0f, true);
		}
		else if (HpRate > 0.3f && LowHealthHandle.IsValid())
		{
			GetMyController()->SetLowHealthFilter(false);
			GetWorldTimerManager().ClearTimer(LowHealthHandle);
			LowHealthComp->Stop();
		}
	}
	

	return CurHp;
}

int APlayerCharacter::SetCurMainAmmo(int32 NewCurAmmo)
{
	CurMainAmmo = FMath::Clamp(NewCurAmmo, 0, MaxMainAmmo);
	OnMainAmmoChanged.ExecuteIfBound(CurMainAmmo, CurRemainMainAmmo);

	if (CurMainAmmo == 0)
	{
		StopShoot();
	}

	return CurMainAmmo;
}

int APlayerCharacter::SetRemainMainAmmo(int32 NewRemainAmmo)
{
	CurRemainMainAmmo = FMath::Clamp(NewRemainAmmo, 0, MaxRemainMainAmmo); // 500 is temp
	OnMainAmmoChanged.ExecuteIfBound(CurMainAmmo, CurRemainMainAmmo);

	return CurRemainMainAmmo;
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
	if (IsDead || IsClear)
	{
		return;
	}

	// Sound
	USoundBase* Damaged = SFX_OnDamaged[FMath::RandRange(0, SFX_OnDamaged.Num() - 1)];
	UGameplayStatics::PlaySound2D(GetWorld(), Damaged);

	SetHp(CurHp - InDamage);
	OnPlayerDamaged.ExecuteIfBound(IsDead);
}

void APlayerCharacter::OnDie()
{
	IsDead = true;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	StopShoot();

	// Low Health Filter
	GetMyController()->SetLowHealthFilter(false);
	GetWorldTimerManager().ClearTimer(LowHealthHandle);
	LowHealthComp->Stop();

	// Animation
	PlayMontage(DeadMontage);
	PlayerCamera->AddRelativeLocation(FVector(-100, 0, 200));
	AddControllerPitchInput(-90);

	// Sound
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_OnDie);
	
	BgmComp->Stop();
	BgmComp->SetSound(BGM_GameOver);
	BgmComp->Play();

	// GameOver UI
	GetMyController()->GameOver();
}

void APlayerCharacter::ShowProcessUI()
{
	if (IsHealing)
	{
		GetMyController()->ShowProcessUI(FText::FromString(TEXT("Healing...")), HealMontage->GetPlayLength());
	}
}

void APlayerCharacter::PlayMontage(UAnimMontage* NewMontage)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(NewMontage);
}

void APlayerCharacter::TankEncounter()
{
	BgmComp->Stop();
	BgmComp->SetSound(BGM_Tank);
	BgmComp->Play();
}

void APlayerCharacter::TankDie()
{
	BgmComp->FadeOut(4.0f, 0.001f);
	
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda(
		[&]() {
			BgmComp->SetSound(BGM_Normal);
			BgmComp->FadeIn(2.0f);
		}), 4.0f, false);

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

	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FVector CameraLocation = CameraManager->GetCameraLocation();
	FVector Destination = CameraLocation + CameraManager->GetActorForwardVector() * 1000;

	float XOffset = FMath::RandRange(-1, 1) > 0 ? (1 - CurShootAccurancy) : -(1 - CurShootAccurancy);
	float YOffset = FMath::RandRange(-1, 1) > 0 ? (1 - CurShootAccurancy) : -(1 - CurShootAccurancy);
	Destination.X += XOffset;
	Destination.Y += YOffset;

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	FVector FireDirectionVec = (Destination - FireSocketLocation).GetSafeNormal();
	
	ABullet* Projectile = GetWorld()->SpawnActor<ABullet>(BulletClass, MuzzleLocation, MuzzleRotator, Params);
	if (Projectile)
	{
		Projectile->Fire(FireDirectionVec, GetAttackPower());
	}

	if (CurHand == EHandType::MainWeapon)
	{
		SetCurMainAmmo(CurMainAmmo - 1);
		UGameplayStatics::PlaySound2D(GetWorld(), SFX_RifleFire, 1.3f);
	}
	else
	{
		SetCurSubAmmo(CurSubAmmo - 1);
		UGameplayStatics::PlaySound2D(GetWorld(), SFX_PistolFire, 0.7f);
	}

	// Accuracy
	SetShootAccurancy(CurShootAccurancy - GetShootDeltaAccurancy());

	// recoil 
	FVector RecoilVec = FVector::DownVector + FVector(FMath::RandRange(-1.0f, 1.0f), 0, 0);
	RecoilVec.Normalize();
	RecoilVec = IsZooming ? RecoilVec * RecoilOffsetInZoom : RecoilVec * RecoilOffsetInNormal;

	AddControllerPitchInput(RecoilVec.Z);
	AddControllerYawInput(RecoilVec.X);

	// Particle
	GunShotParticleComponent->SetActive(false);
	GunShotParticleComponent->SetActive(true);

	// Sound
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_RifleFire);
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
		if (diff >= CurRemainMainAmmo)
		{
			SetCurMainAmmo(CurMainAmmo + CurRemainMainAmmo);
			SetRemainMainAmmo(0);
		}
		else
		{
			SetCurMainAmmo(MaxMainAmmo);
			SetRemainMainAmmo(CurRemainMainAmmo - diff);
		}
	}
	else if (CurHand == EHandType::SubWeapon)
	{
		SetCurSubAmmo(MaxSubAmmo);
	}
	IsReloading = false;

	UE_LOG(LogTemp, Log, TEXT("%d / %d"), CurMainAmmo, CurRemainMainAmmo);
}

bool APlayerCharacter::IsDeadOrClear()
{
	return IsDead || IsClear;
}

void APlayerCharacter::ThrowBegin()
{
	if (RemainGrenade < 1 || IsThrowing)
	{
		return;
	}
	IsThrowing = true;

	PlayMontage(ThrowGrenadeMontage);
}

void APlayerCharacter::ThrowGrenade()
{
	const FVector ThrowLocation = GetMesh()->GetSocketLocation(TEXT("WeaponSocket"));
	const FRotator ThrowRotator = GetMesh()->GetSocketRotation(TEXT("WeaponSocket"));

	const FRotator ControllerRotator = Controller->GetControlRotation();
	const FVector ControllerForwardVec = FRotationMatrix(ControllerRotator).GetUnitAxis(EAxis::X);
	const FVector ControllerUpVec = FRotationMatrix(ControllerRotator).GetUnitAxis(EAxis::Z) * 0.2f;
	FVector ThrowDirVec = (ControllerForwardVec + ControllerUpVec);
	ThrowDirVec.Normalize();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	AThrowableWeaponBase* Throwable = GetWorld()->SpawnActor<AThrowableWeaponBase>(GrenadeClass, ThrowLocation, ThrowRotator, Params);
	if (Throwable)
	{
		Throwable->Throw(ThrowDirVec);
	}
	SetRemainGrenade(RemainGrenade - 1);
	
	if (RemainGrenade == 0)
	{
		WeaponComponent->SetStaticMesh(nullptr);
	}

	IsThrowing = false;
}

void APlayerCharacter::ThrowEnd()
{
	IsThrowing = false;
}

void APlayerCharacter::MeleeAttackHit()
{
	const FVector ForwardVec = FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::X);
	FVector AttackCenterVec = GetActorLocation() + MeleeAttackMuzzleOffset + ForwardVec * GetCapsuleComponent()->GetUnscaledCapsuleRadius() * 1.5f;

	TArray<FOverlapResult> OverlapResults;
	bool IsHitted = GetWorld()->OverlapMultiByProfile(OverlapResults, AttackCenterVec, FQuat::MakeFromRotator(GetController()->GetControlRotation()),
														TEXT("Enemy"), FCollisionShape::MakeBox(MeleeAttackBoxVec));

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

				Zombie->OnKnuckback();
				/*FVector force = DirectionVec * KnuckbackPower;
				force = force.GetClampedToMaxSize(KnuckbackPower);
				auto comp = OverlapResults[i].GetComponent();
				if (comp && comp->IsSimulatingPhysics())
				{
					OverlapResults[i].GetComponent()->AddForceAtLocation(GetActorForwardVector() * KnuckbackPower, Zombie->GetActorLocation());
				}*/
				Zombie->SetActorLocation(Zombie->GetActorLocation() + DirectionVec * KnuckbackPower);
				Zombie->OnDamaged(MeleeAttackPower);
				UE_LOG(LogTemp, Log, TEXT("Melee Attack Hit: %d"), MeleeAttackPower);
			}
		}
	}
}

void APlayerCharacter::MeleeAttackEnd()
{
	IsMeleeAttackDelay = false;
}

void APlayerCharacter::SetNearbyItem(AItemBase* InItem)
{
	if (NearbyItem)
	{
		NearbyItem->OutlineOff();
	}

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

void APlayerCharacter::GameClear()
{
	IsClear = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	WeaponComponent->SetStaticMesh(nullptr);

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	StopShoot();

	AMyPlayerController* Mycontroller = GetMyController();
	Mycontroller->GameClear();

	BgmComp->Stop();
	BgmComp->SetSound(BGM_GameClear);
	BgmComp->Play();

	FTimerHandle ExitHandle;
	GetWorldTimerManager().SetTimer(ExitHandle, FTimerDelegate::CreateLambda(
		[&]() {
			GetMesh()->SetHiddenInGame(true);
		}), 4.0f, false);

	FActorSpawnParameters Params;
	AHelicopterPawn* Helicopter = Cast<AHelicopterPawn>(GetWorld()->SpawnActor<AHelicopterPawn>(AHelicopterPawn::StaticClass(), FVector(43103, 10469, 2451), FRotator(0, 110, 0), Params));
	Mycontroller->UnPossess();
	Mycontroller->Possess(Helicopter);
}
