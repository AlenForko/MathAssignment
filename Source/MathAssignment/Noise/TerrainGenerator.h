// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "TerrainGenerator.generated.h"


class UProceduralMeshComponent;
UCLASS()
class MATHASSIGNMENT_API ATerrainGenerator : public AActor
{
	GENERATED_BODY()
	
public:
	ATerrainGenerator();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	UProceduralMeshComponent* ProceduralMeshComponent;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* Material;

	UPROPERTY(EditAnywhere)
	float ZMultiplier = 1.f;

	UPROPERTY(EditAnywhere)
	float UVScale = 0.0f;

	UPROPERTY(EditAnywhere)
	float NoiseScale = 1.f;
	
	float Scale = 100;
	
	TArray<FVector> Vertices;
	
	TArray<int32> Triangles;
	
	TArray<FVector2D> UV0;
	
	TArray<FVector> Normals;
	
	TArray<struct FProcMeshTangent> Tangents;
	
	UPROPERTY(EditAnywhere)
	int32 GridSize;

	float CellSize;
	
	void GenerateTerrain();
};
