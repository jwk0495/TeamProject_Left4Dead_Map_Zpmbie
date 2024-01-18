// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/MainWeapon.h"

AMainWeapon::AMainWeapon()
{
	AttackPower = 30;
	WeaponLocation = FVector(23.81f, 11.85f, -31.33f);
	WeaponRotation = FRotator(11.45f, 93.43f, 78.43f);
	WeaponScale = FVector(2.3f, 2.3f, 2.5f);
}
