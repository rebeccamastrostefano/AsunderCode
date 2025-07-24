#include "SplitLineActor.h"
#include "Components/SplineMeshComponent.h"
#include "CWTP_Project/DoublePlayerController.h"
#include "CWTP_Project/Player1Character.h"
#include "CWTP_Project/Player2Character.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Components/BoxComponent.h"

ASplitLineActor::ASplitLineActor()
{
    PrimaryActorTick.bCanEverTick = true;

    Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    RootComponent = Spline;
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
    UpdateSpline();
    UpdateSplineMeshes();
}

void ASplitLineActor::OnConstruction(const FTransform &Transform)
{
    Super::OnConstruction(Transform);
    UpdateSpline();
    UpdateSplineMeshes();
}

void ASplitLineActor::UpdateSpline()
{
    if (Player1 != nullptr && Player2 != nullptr)
    {
        FVector Player1Loc = Player1->GetActorLocation();
        FVector Player2Loc = Player2->GetActorLocation();

        // Flatten to YZ plane (ignore depth/X axis)
        Player1Loc.X = 0.f;
        Player2Loc.X = 0.f;
        // Update material parameters
        SendParametersToMaterial(Player1Loc, Player2Loc);

        // 1. Midpoint
        FVector MidPoint = (Player1Loc + Player2Loc) / 2.0f;
        
        // 2. Direction vector between players (on YZ only)
        FVector BetweenVector = (Player2Loc - Player1Loc).GetSafeNormal();
        
        // 3. Get perpendicular vector in YZ plane
        FVector2D Dir2D = FVector2D(BetweenVector.Y, BetweenVector.Z);
        FVector2D Perp2D(-Dir2D.Y, Dir2D.X); // Rotate 90° CCW
        
        // Reconstruct back to 3D with X = 0 (flat in depth)
        FVector PerpVector = FVector(0.f, Perp2D.X, Perp2D.Y);

        // 4. Set Spline points
        float LineLength = 3000.0f; // however long the divider should be
                
        FVector PointA = MidPoint + PerpVector * LineLength;
        FVector PointB = MidPoint - PerpVector * LineLength;

        Spline->ClearSplinePoints();
        Spline->AddSplinePoint(PointA, ESplineCoordinateSpace::World);
        Spline->AddSplinePoint(PointB, ESplineCoordinateSpace::World);
        Spline->UpdateSpline();

        // Update The Collider
        FVector Perp3D = FVector(0.f, Perp2D.X, Perp2D.Y); // In 3D, keeping X=0
        FRotator Rotation = Perp3D.Rotation(); // Align the "X" of the box to this
        Rotation.Roll = 90.f;

        SplitCollider->SetWorldLocation(MidPoint);
        SplitCollider->SetWorldRotation(Rotation);
    }
}

void ASplitLineActor::UpdateSplineMeshes()
{
    if (!MeshSegments[0]) MeshSegments.SetNum(0);
    while (MeshSegments.Num() < NumSplinePoints - 1)
    {
        USplineMeshComponent* NewMesh = NewObject<USplineMeshComponent>(this);

        NewMesh->SetMobility(EComponentMobility::Movable);
        NewMesh->RegisterComponentWithWorld(GetWorld());
        NewMesh->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
        MeshSegments.Add(NewMesh);
    }

    // Hide extra meshes if NumSplinePoints decreases
    for (int32 i = NumSplinePoints - 1; i < MeshSegments.Num(); ++i)
    {
        if (MeshSegments[i])
        {
            MeshSegments[i]->DestroyComponent();
        }
    }
    MeshSegments.SetNum(NumSplinePoints - 1);

    for (int i = 0; i < NumSplinePoints - 1; ++i)
    {
        FVector StartPos, StartTangent, EndPos, EndTangent;
        Spline->GetLocationAndTangentAtSplinePoint(i, StartPos, StartTangent, ESplineCoordinateSpace::World);
        Spline->GetLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent, ESplineCoordinateSpace::World);

        if (MeshSegments[i])
        {
            MeshSegments[i]->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);
            MeshSegments[i]->SetStaticMesh(SegmentMesh);
            MeshSegments[i]->SetMaterial(0, SegmentMaterial);
            MeshSegments[i]->SetForwardAxis(ESplineMeshAxis::Y);
        }
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

    UpdateSpline();
    UpdateSplineMeshes();
}

void ASplitLineActor::SendParametersToMaterial(FVector Player1Pos, FVector Player2Pos)
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();

    // Get screen positions (0-1 UV coordinates)
    FVector2D Player1Screen, Player2Screen;
    PC->ProjectWorldLocationToScreen(Player1Pos, Player1Screen);
    PC->ProjectWorldLocationToScreen(Player2Pos, Player2Screen);

    // Pass these to material as Vector2 parameters
    UMaterialParameterCollectionInstance* CollectionInstance = GetWorld()->GetParameterCollectionInstance(MaterialParameterCollection);
    CollectionInstance->SetVectorParameterValue("Player1Pos", FLinearColor(Player1Screen.X, Player1Screen.Y, 0, 0));
    CollectionInstance->SetVectorParameterValue("Player2Pos", FLinearColor(Player2Screen.X, Player2Screen.Y, 0, 0));
}