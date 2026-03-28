// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcMeshFromStatic.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
AProcMeshFromStatic::AProcMeshFromStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

		//Heather: Create the procedural mesh component and set it as the root component. Then create the static mesh component and attach it to the procedural mesh.
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Proc Mesh"));
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));

	RootComponent = procMesh;
	baseMesh->SetupAttachment(procMesh);
}

// Called when the game starts or when spawned
void AProcMeshFromStatic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProcMeshFromStatic::PostActorCreated()
{
	Super::PostActorCreated();

		//Heather: Get the mesh data from the static mesh and use it to create the procedural mesh.
	GetMeshData();
}

void AProcMeshFromStatic::PostLoad()
{
	Super::PostLoad();

		//Heather: Get the mesh data from the static mesh and use it to create the procedural mesh.
	GetMeshData();
}

// Called every frame
void AProcMeshFromStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProcMeshFromStatic::GetMeshData()
{
		//Heather: Get the mesh data from the static mesh and use it to create the procedural mesh.
	UStaticMesh* mesh = baseMesh->GetStaticMesh();

		//Heather: If the mesh is valid, get the mesh data and use it to create the procedural mesh.
	if (mesh) 
	{
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Vertices, Triangles, Normals, UV0, Tangents);
		procMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertexColors, Tangents);
		CreateMesh();
	}
}

void AProcMeshFromStatic::CreateMesh()
{
		//Heather: If the mesh is valid, create the procedural mesh using the mesh data.
	if (baseMesh) 
	{
		procMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, UpVertexColors, Tangents, true);
	}
}

