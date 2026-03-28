// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class GAM415_FPS_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();

		//Heather: These are the properties that will be used to generate the terrain.
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int XSize = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int YSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
	float ZMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	float NoiseScale = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float Scale = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float UVScale = 0;

	UPROPERTY(EditAnywhere)
	float radius;

	UPROPERTY(EditAnywhere)
	FVector Depth;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

		//Heather: This is the procedural mesh component that will be used to generate the terrain.
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Mat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		//Heather: This is the function that will be called when the player hits the terrain.
	UFUNCTION()
	void AlterMesh(FVector impactpoint);

private:

		//Heather: These are the arrays that will be used to generate the terrain.
	UProceduralMeshComponent* procMesh;
	TArray<FVector> vertices;
	TArray<int> triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> normals;
	TArray<FColor> UpVertexColors;

		//Heather: This is the section ID that will be used to generate the terrain.
	int sectionID = 0;

		//Heather: These are the functions that will be used to generate the terrain.
	void CreateVertices();
	void CreateTriangles();

};
