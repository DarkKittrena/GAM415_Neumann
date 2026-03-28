// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcPlane.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AProcPlane::AProcPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

		//Heather: We create the procedural mesh component and set the material for it
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Proc Mesh"));

	

}

// Called when the game starts or when spawned
void AProcPlane::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProcPlane::PostActorCreated()
{
	Super::PostActorCreated();

		//Heather: We call create mesh here becasue when we create the actor in the level, we want to make sure that the mesh is created and visible
	CreateMesh();

	if (planeMat)
	{
		procMesh->SetMaterial(0, planeMat);
	}
}

void AProcPlane::PostLoad()
{
	Super::PostLoad();

		//Heather: We call create mesh here because when we load the actor in the level, we want to make sure that the mesh is created and visible
	CreateMesh();

	if (planeMat)
	{
		procMesh->SetMaterial(0, planeMat);
	}
}

// Called every frame
void AProcPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProcPlane::CreateMesh()
{
		//Heather: This is where we will create the mesh for the plane. We will use the procedural mesh component to create the mesh.
	procMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}

