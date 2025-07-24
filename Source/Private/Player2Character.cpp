// Fill out your copyright notice in the Description page of Project Settings.


#include "Player2Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayer2Character::APlayer2Character()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

void APlayer2Character::BeginPlay()
{
    Super::BeginPlay();
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;
    GetCharacterMovement()->GravityScale = 1.f;
}

