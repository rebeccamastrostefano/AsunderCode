#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "Components/BoxComponent.h"
#include "SplitLineActor.generated.h"

UCLASS()
class CWTP_PROJECT_API ASplitLineActor : public AActor
{
	GENERATED_BODY()

public:
	ASplitLineActor();

	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform &Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Split Line")
	int32 NumSplinePoints = 10;

	UPROPERTY(EditAnywhere, Category = "Split Line")
	UStaticMesh *SegmentMesh;
	
	UPROPERTY(EditAnywhere, Category = "Split Line")
	UMaterialInterface *SegmentMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Split Line")
	UMaterialParameterCollection *MaterialParameterCollection;

	UPROPERTY(EditAnywhere, Category = "Split Line")
	float ColliderWidth = 5000.0f; // How wide across the world (X axis)

	UPROPERTY(EditAnywhere, Category = "Split Line")
	float ColliderThickness = 10.0f; // How thick the wall is (YZ plane)

	UPROPERTY(EditAnywhere, Category = "Split Line")
	float ColliderHeight = 2000.0f; // Vertical height of the wall

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	AActor *Player1;

	UPROPERTY()
	AActor *Player2;

	UPROPERTY()
	USplineComponent *Spline;

	UPROPERTY()
	UBoxComponent *SplitCollider;

	UPROPERTY()
	bool bIsFrozen = false;

	UPROPERTY()
	TArray<USplineMeshComponent *> MeshSegments;

	void UpdateSpline();
	void UpdateSplineMeshes();
	void GetPlayers();
	void SendParametersToMaterial(FVector Player1Pos, FVector Player2Pos);
};
