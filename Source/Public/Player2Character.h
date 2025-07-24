// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player2Character.generated.h"

UCLASS()
class CWTP_PROJECT_API APlayer2Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer2Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
