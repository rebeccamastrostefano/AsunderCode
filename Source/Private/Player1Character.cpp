// Fill out your copyright notice in the Description page of Project Settings.


#include "Player1Character.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayer1Character::APlayer1Character()
{
    // Enable rotation based on movement
    GetCharacterMovement()->bOrientRotationToMovement = true;
}

void APlayer1Character::BeginPlay()
{
    Super::BeginPlay();
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->FallingLateralFriction = 1.0f;
    GetCharacterMovement()->AirControl = 0.5f;

    if (GetCharacterMovement())
    {
        GetCharacterMovement()->GravityScale = UnderwaterGravityScale;
        GetCharacterMovement()->JumpZVelocity = UnderwaterJumpZVelocity;
    }
}
