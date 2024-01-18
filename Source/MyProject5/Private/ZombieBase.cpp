// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/AIController.h"

// Sets default values
AZombieBase::AZombieBase()
{
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AZombieBase::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AZombieBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AZombieBase::OnDamaged(int32 InDamage)
{
    CurHp = FMath::Clamp(CurHp - InDamage, 0, MaxHp);

    if (CurHp == 0)
        OnDie();
}

void AZombieBase::OnKnuckback()
{
    GetCharacterMovement()->SetMovementMode(MOVE_None);

    if (KnuckbackHandle.IsValid())
    {
        GetWorld()->GetTimerManager().ClearTimer(KnuckbackHandle);
    }

    GetWorld()->GetTimerManager().SetTimer(KnuckbackHandle, FTimerDelegate::CreateLambda(
        [&]()
        {
            GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        }
    ), KnuckbackTime, false);
}
