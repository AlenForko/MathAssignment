// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainGenerator.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
ATerrainGenerator::ATerrainGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
	SetRootComponent(ProceduralMeshComponent);

}

// Called when the game starts or when spawned
void ATerrainGenerator::BeginPlay()
{
	Super::BeginPlay();
	NoiseScale = FMath::RandRange(0.01, 0.1);

	Vertices.Reset();
	Triangles.Reset();
	UV0.Reset();
	
	GenerateTerrain();
}

void ATerrainGenerator::GenerateTerrain()
{
    for (int32 i = 0; i < GridSize; ++i)
    {
        for (int32 j = 0; j < GridSize; ++j)
        {
	        
            float Z = FMath::PerlinNoise2D(
            	FVector2D(i * NoiseScale + 0.1f,
            	j * NoiseScale + 0.1f))
        		* ZMultiplier;
        	
            Vertices.Add(FVector(i * Scale, j * Scale, Z));
        	UV0.Add(FVector2D(i * UVScale, j * UVScale));
        }
    }

	//Triangles generation
    for (int32 i = 0; i < GridSize - 1; ++i)
    {
        for (int32 j = 0; j < GridSize - 1; ++j)
        {
            int32 Index = i * GridSize + j;

            Triangles.Add(Index);
            Triangles.Add(Index + 1);
            Triangles.Add(Index + GridSize);

            Triangles.Add(Index + 1);
            Triangles.Add(Index + GridSize + 1);
            Triangles.Add(Index + GridSize);
        }
    }

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, Normals, Tangents);
	
    ProceduralMeshComponent->CreateMeshSection(
        0,
        Vertices,
        Triangles,
        Normals,
        UV0,
        TArray<FColor>(),
        Tangents,
        true);

	ProceduralMeshComponent->SetMaterial(0, Material);
}
