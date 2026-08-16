// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProcTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrain::APerlinProcTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

		//Heather: Create the procedural mesh component and set it as the root component.
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	RootComponent = procMesh;
}

// Called when the game starts or when spawned
void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();

		//Heather: Create the vertices and triangles for the procedural mesh and use them to create the mesh section.
	CreateVertices();
	CreateTriangles();
	procMesh->CreateMeshSection(sectionID, vertices, triangles, normals, UV0, UpVertexColors, TArray<FProcMeshTangent>(), true);

		//Heather: Set the material for the procedural mesh.
	procMesh->SetMaterial(0, Mat);
	
}

// Called every frame
void APerlinProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerlinProcTerrain::AlterMesh(FVector impactpoint)
{
		//Heather: Use a for loop to iterate through the vertices of the procedural mesh.
	for (int i = 0; i < vertices.Num(); i++)
	{
			//Heather: Calculate the distance from the vertex to the impact point.
		FVector tempVector = impactpoint - this->GetActorLocation();

			//Heather: Check if the vertex is within the radius of the impact point. If it is, move the vertex down by the depth value and update the mesh section.
		if (FVector(vertices[i] - tempVector).Size() < radius) 
		{
			vertices[i] = vertices[i] - Depth;
			procMesh->UpdateMeshSection(sectionID, vertices, normals, UV0, UpVertexColors, TArray<FProcMeshTangent>());
		}
	}
}

void APerlinProcTerrain::CreateVertices()
{
		//Heather: Use nested for loops to iterate through the X and Y values and generate the vertices for the procedural mesh.
	for (int X = 0; X <= XSize; X++)
	{
		for (int Y = 0; Y <= YSize; Y++)
		{
				//Heather: Use Perlin noise to generate the Z value for the vertex based on the X and Y values. Then add the vertex to the vertices array and the UV coordinate to the UV0 array.
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier;
			vertices.Add(FVector(X * Scale, Y * Scale, Z));
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
			
		}
	}
}

void APerlinProcTerrain::CreateTriangles()
{
		//Heather: This is the vertex index that will be used to generate the triangles for the procedural mesh.
	int vertex = 0;

		//Heather: Use nested for loops to iterate through the X and Y values and generate the triangles for the procedural mesh.
	for (int X = 0; X < XSize; X++)
	{
		for (int Y = 0; Y < YSize; Y++)
		{
				//Heather: Use the vertex index to generate the triangles for the procedural mesh. Then add the triangle indices to the triangles array.
			triangles.Add(vertex);
			triangles.Add(vertex + 1);
			triangles.Add(vertex + YSize + 1);
			triangles.Add(vertex + 1);
			triangles.Add(vertex + YSize + 2);
			triangles.Add(vertex + YSize + 1);
			vertex++;
		}
		vertex++;
	}
}

