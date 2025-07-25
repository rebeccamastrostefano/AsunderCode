#include "SplitLineActor.h"
#include "CWTP_Project/DoublePlayerController.h"
#include "CWTP_Project/Player1Character.h"
#include "CWTP_Project/Player2Character.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Components/BoxComponent.h"

ASplitLineActor::ASplitLineActor()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SplitRoot"));

    //Create the collider and set up size and collisions
    SplitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("SplitCollider"));
    SplitCollider->SetupAttachment(RootComponent);
    SplitCollider->SetCollisionProfileName("BlockAllDynamic");
    SplitCollider->SetGenerateOverlapEvents(true);
    SplitCollider->SetBoxExtent(FVector(ColliderWidth / 2.f, ColliderThickness / 2.f, ColliderHeight / 2.f));
}

void ASplitLineActor::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimerForNextTick(this, &ASplitLineActor::GetPlayers);
}

void ASplitLineActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateSplitCollider();
}

void ASplitLineActor::OnConstruction(const FTransform &Transform)
{
    Super::OnConstruction(Transform);
    UpdateSplitCollider();
}

// Method that updates the Split Line Collider
void ASplitLineActor::UpdateSplitCollider()
{
    if (Player1 != nullptr && Player2 != nullptr)
    {
        FVector Player1Loc = Player1->GetActorLocation();
        FVector Player2Loc = Player2->GetActorLocation();

        // Flatten to YZ plane
        Player1Loc.X = 0.f;
        Player2Loc.X = 0.f;

        // Update material parameters
        SendParametersToMaterial(Player1Loc, Player2Loc);

        //Midpoint
        FVector MidPoint = (Player1Loc + Player2Loc) / 2.0f;
        
        //Direction vector between players
        FVector BetweenVector = (Player2Loc - Player1Loc).GetSafeNormal();
        
        //Get perpendicular vector
        FVector2D Dir2D = FVector2D(BetweenVector.Y, BetweenVector.Z);
        FVector2D Perp2D(-Dir2D.Y, Dir2D.X); // Rotate 90°

        // Update The Collider
        FVector Perp3D = FVector(0.f, Perp2D.X, Perp2D.Y);
        FRotator Rotation = Perp3D.Rotation();
        Rotation.Roll = 90.f;

        SplitCollider->SetWorldLocation(MidPoint);
        SplitCollider->SetWorldRotation(Rotation);
    }
}

void ASplitLineActor::GetPlayers()
{
    if (APlayerController *PC = GetWorld()->GetFirstPlayerController())
    {
        if (ADoublePlayerController *DPC = Cast<ADoublePlayerController>(PC))
        {
            Player1 = Cast<AActor>(DPC->Player1);
            Player2 = Cast<AActor>(DPC->Player2);
        }
    }

    UpdateSplitCollider();
}

void ASplitLineActor::SendParametersToMaterial(FVector Player1Pos, FVector Player2Pos)
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();

    // Get screen positions
    FVector2D Player1Screen, Player2Screen;
    PC->ProjectWorldLocationToScreen(Player1Pos, Player1Screen);
    PC->ProjectWorldLocationToScreen(Player2Pos, Player2Screen);

    // Pass these to material as Vector2 parameters
    UMaterialParameterCollectionInstance* CollectionInstance = GetWorld()->GetParameterCollectionInstance(MaterialParameterCollection);
    CollectionInstance->SetVectorParameterValue("Player1Pos", FLinearColor(Player1Screen.X, Player1Screen.Y, 0, 0));
    CollectionInstance->SetVectorParameterValue("Player2Pos", FLinearColor(Player2Screen.X, Player2Screen.Y, 0, 0));
}