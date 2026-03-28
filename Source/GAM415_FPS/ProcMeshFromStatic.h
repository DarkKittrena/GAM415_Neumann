// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProcMeshFromStatic.generated.h"

UCLASS()
class GAM415_FPS_API AProcMeshFromStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcMeshFromStatic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		//Heather: This is the data we need to create a procedural mesh.
	UPROPERTY(EditAnywhere)
	TArray<FVector> Vertices;

	UPROPERTY(EditAnywhere)
	TArray<int> Triangles;

	UPROPERTY(EditAnywhere)
	TArray<FVector> Normals;

	UPROPERTY(EditAnywhere)
	TArray<FVector2D> UV0;

	UPROPERTY(EditAnywhere)
	TArray<FLinearColor> VertexColors;

	UPROPERTY(EditAnywhere)
	TArray<FColor> UpVertexColors;

	UPROPERTY(EditAnywhere)
	TArray<FProcMeshTangent> Tangents;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* baseMesh;

private:

		//Heather: This is the procedural mesh component we will create and add to the actor.
	UProceduralMeshComponent* procMesh;
	void GetMeshData();
	void CreateMesh();



};
