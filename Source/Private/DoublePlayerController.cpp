#include "DoublePlayerController.h"
#include "Player1Character.h"
#include "Player2Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"  // Include for UCameraComponent
#include "GameFramework/SpringArmComponent.h"  // Include for USpringArmComponent
#include "InputActionValue.h"

ADoublePlayerController::ADoublePlayerController()
{
    Player1 = nullptr;
    Player2 = nullptr;
    InputSubsystem = nullptr;
}

void ADoublePlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Initialize the Input Subsystem
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

        if (InputSubsystem)
        {
            if (Player1MappingContext)
            {
                InputSubsystem->AddMappingContext(Player1MappingContext, 0);
                UE_LOG(LogTemp, Warning, TEXT("Player 1 Mapping Context added"));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Player1MappingContext is null"));
            }

            if (Player2MappingContext)
            {
                InputSubsystem->AddMappingContext(Player2MappingContext, 1);
                UE_LOG(LogTemp, Warning, TEXT("Player 2 Mapping Context added"));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Player2MappingContext is null"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Enhanced Input Subsystem not available"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("LocalPlayer not found for PlayerController"));
    }

    // Set up custom camera for Player 1
    if (Player1 && Player2)
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetViewTargetWithBlend(Player1, 0.5f); // Player1 as the default view target
        }
    }
}

void ADoublePlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADoublePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // Bind Player 1 Actions
        if (MovePlayer1Action)
        {
            EnhancedInput->BindAction(MovePlayer1Action, ETriggerEvent::Triggered, this, &ADoublePlayerController::MovePlayer1);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("MovePlayer1Action is null"));
        }

        if (JumpPlayer1Action)
        {
            EnhancedInput->BindAction(JumpPlayer1Action, ETriggerEvent::Started, this, &ADoublePlayerController::JumpPlayer1);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("JumpPlayer1Action is null"));
        }

        // Bind Player 2 Actions
        if (MovePlayer2Action)
        {
            EnhancedInput->BindAction(MovePlayer2Action, ETriggerEvent::Triggered, this, &ADoublePlayerController::MovePlayer2);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("MovePlayer2Action is null"));
        }
         
        if (JumpPlayer2Action)
        {
            EnhancedInput->BindAction(JumpPlayer2Action, ETriggerEvent::Started, this, &ADoublePlayerController::JumpPlayer2);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("JumpPlayer2Action is null"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("InputComponent is not an EnhancedInputComponent"));
    }
}


void ADoublePlayerController::SetPlayer1Pawn(APlayer1Character* InPlayer1)
{
    Player1 = InPlayer1;
    if (Player1)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player1 Pawn assigned to Controller"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Player1 Pawn is null"));
    }
}

void ADoublePlayerController::SetPlayer2Pawn(APlayer2Character* InPlayer2)
{
    Player2 = InPlayer2;
    if (Player2)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player2 Pawn assigned to Controller"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Player2 Pawn is null"));
    }
}

void ADoublePlayerController::MovePlayer1(const FInputActionValue& Value)
{
    if (Player1)
    {
        FVector2D Movement = Value.Get<FVector2D>();
        if (!Movement.IsNearlyZero())  // Ignore zero movement
        {
            Player1->AddMovementInput(FVector::ForwardVector, Movement.Y);
            Player1->AddMovementInput(FVector::RightVector, Movement.X);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Player1 Pawn is null; cannot process input"));
    }
}

void ADoublePlayerController::MovePlayer2(const FInputActionValue& Value)
{
    if (Player2)
    {
        FVector2D Movement = Value.Get<FVector2D>();
        if (!Movement.IsNearlyZero())  // Ignore zero movement
        {
            Player2->AddMovementInput(FVector::ForwardVector, Movement.Y);
            Player2->AddMovementInput(FVector::RightVector, Movement.X);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Player2 Pawn is null; cannot process input"));
    }
}

void ADoublePlayerController::JumpPlayer1(const FInputActionValue& Value)
{
    if (Player1)
    {
        Player1->Jump();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Player1 Pawn is null; cannot process input"));
    }
}

void ADoublePlayerController::JumpPlayer2(const FInputActionValue& Value)
{
    if (Player2)
    {
        Player2->Jump();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Player2 Pawn is null; cannot process input"));
    }
}

