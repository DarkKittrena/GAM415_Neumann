// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProcPlane.generated.h"

class UProceduralMeshComponent;

UCLASS()
class GAM415_FPS_API AProcPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

		//Heather: This is the function that will be called after the actor is created
	virtual void PostActorCreated() override;

		//Heather: This is the function that will be called after the actor is loaded
	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		//Heather: These are the procedural mesh components that will be used to help create the plane
	UPROPERTY(EditAnywhere)
	TArray<FVector> Vertices;

	UPROPERTY(EditAnywhere)
	TArray<int> Triangles;

	UPROPERTY(EditAnywhere)
	TArray<FVector2D> UV0;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* planeMat;

		//Heather: This is the function that will be called to create the mesh
	UFUNCTION()
	void CreateMesh();

private:

		//Heather: This is the procedural mesh component that will be used to create the plane
	UProceduralMeshComponent* procMesh;

};
