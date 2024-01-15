// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/MainWeapon.h"

AMainWeapon::AMainWeapon()
{
	AttackPower = 30;
	WeaponLocation = FVector(26.0f, 8.64f, -26.70f);
	WeaponRotation = FRotator(16.42f, 87.06f, 82.43f);
	WeaponScale = FVector(2.3f, 2.3f, 2.5f);
}
