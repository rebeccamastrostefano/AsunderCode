// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player1Character.generated.h"

UCLASS()
class CWTP_PROJECT_API APlayer1Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer1Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Jumping")
	float UnderwaterGravityScale = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Jumping")
	float UnderwaterJumpZVelocity = 300.f;
};
