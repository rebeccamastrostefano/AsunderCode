// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DoubleSideScrollerCamera.generated.h"

UCLASS()
class CWTP_PROJECT_API ADoubleSideScrollerCamera : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoubleSideScrollerCamera();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Function to follow players
	void UpdateCameraPosition(AActor* Player1, AActor* Player2, float DeltaTime);

protected:
	// Camera offset and settings
	UPROPERTY(EditAnywhere)
	float CameraDistance = 500.0f;

	UPROPERTY(EditAnywhere)
	FVector CameraOffset = FVector(0.0f, 0.0f, 200.0f);

	UPROPERTY(EditAnywhere)
	float CameraLagSpeed = 5.0f;

	UPROPERTY(EditAnywhere)
	float FixedZOffset = 100.0f;
	
	UPROPERTY(EditAnywhere)
	float FixedXOffset = 0.0f;

	UPROPERTY(EditAnywhere)
	float ZoomFactor = 0.5f;

	UPROPERTY(EditAnywhere)
	float MinZoom = 0.5f;

	UPROPERTY(EditAnywhere)
	float MaxZoom = 2.0f;

	UPROPERTY(EditAnywhere)
	float CameraTiltDegrees = -8.0f;
};
