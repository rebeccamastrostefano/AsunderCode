// Fill out your copyright notice in the Description page of Project Settings.

#include "DoubleSideScrollerCamera.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADoubleSideScrollerCamera::ADoubleSideScrollerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the Camera Boom (Spring Arm)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = CameraLagSpeed;
	CameraBoom->bDoCollisionTest = false; // No collision for side-scrolling camera

	// Create Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom);
	CameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ADoubleSideScrollerCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoubleSideScrollerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get the two player characters
	AActor* Player1 = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AActor* Player2 = UGameplayStatics::GetPlayerPawn(GetWorld(), 1);

	UpdateCameraPosition(Player1, Player2, DeltaTime);
}

// Update camera position to follow both players smoothly
void ADoubleSideScrollerCamera::UpdateCameraPosition(AActor* Player1, AActor* Player2, float DeltaTime)
{
	if (Player1 && Player2)
	{
		FVector Player1Pos = Player1->GetActorLocation();
		FVector Player2Pos = Player2->GetActorLocation();

		// Calculate the midpoint in 2D (X and Y only, ignore Z)
		FVector MidPoint = (Player1Pos + Player2Pos) / 2.0f;
		MidPoint.Z += FixedZOffset; // Keep the camera at a fixed Z height for side-scrolling
		MidPoint.X = FixedXOffset;

		// Adjust the camera's arm length based on horizontal distance
		float DistanceX = FMath::Abs(Player1Pos.X - Player2Pos.X);
		float NewArmLength = FMath::Clamp(DistanceX * ZoomFactor, MinZoom, MaxZoom);
		CameraBoom->TargetArmLength = NewArmLength;

		// Smoothly move the camera towards the target position
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, MidPoint, DeltaTime, CameraLagSpeed);

		// Set the new location of the camera
		SetActorLocation(NewLocation);

		// Keep camera facing right (side view)
		SetActorRotation(FRotator(CameraTiltDegrees, 0.f, 0.f));
	}
}
