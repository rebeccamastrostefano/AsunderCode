#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DoublePlayerController.generated.h"

class APlayer1Character;
class APlayer2Character;
class UInputMappingContext;

/**
 * Player Controller handling input for two pawns.
 */
UCLASS()
class CWTP_PROJECT_API ADoublePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ADoublePlayerController();

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;

    // Assign pawns
    void SetPlayer1Pawn(APlayer1Character* InPlayer1);
    void SetPlayer2Pawn(APlayer2Character* InPlayer2);
    
    // Pawns for Player 1 and Player 2
    UPROPERTY(BlueprintReadWrite)
    APlayer1Character* Player1;

    UPROPERTY(BlueprintReadWrite)
    APlayer2Character* Player2;

protected:

    // Input Mapping Contexts
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputMappingContext* Player1MappingContext;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputMappingContext* Player2MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MovePlayer1Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MovePlayer2Action;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* JumpPlayer1Action;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* JumpPlayer2Action;

    // Input Subsystem
    UEnhancedInputLocalPlayerSubsystem* InputSubsystem;

    // Input Actions
    void MovePlayer1(const FInputActionValue& Value);
    void MovePlayer2(const FInputActionValue& Value);
    void JumpPlayer1(const FInputActionValue& Value);
    void JumpPlayer2(const FInputActionValue& Value);
};
