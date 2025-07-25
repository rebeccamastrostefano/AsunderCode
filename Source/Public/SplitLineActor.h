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
	
	UPROPERTY(EditAnywhere, Category = "Split Line")
	UMaterialParameterCollection *MaterialParameterCollection;

	UPROPERTY(EditAnywhere, Category = "Split Line")
	float ColliderWidth = 5000.0f; // How wide should the collider be

	UPROPERTY(EditAnywhere, Category = "Split Line")
	float ColliderThickness = 10.0f; // How thick the collider is

	UPROPERTY(EditAnywhere, Category = "Split Line")
	float ColliderHeight = 2000.0f; // How heigh the collider is

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	AActor *Player1;

	UPROPERTY()
	AActor *Player2;

	UPROPERTY()
	UBoxComponent *SplitCollider;

	UPROPERTY()
	bool bIsFrozen = false; //TODO: implement ability to freeze the split in place for a certain time period

	UPROPERTY()
	TArray<USplineMeshComponent *> MeshSegments;

	void UpdateSplitCollider();
	void GetPlayers();
	void SendParametersToMaterial(FVector Player1Pos, FVector Player2Pos);
};
