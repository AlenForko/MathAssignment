// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IntersectionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MATHASSIGNMENT_API UIntersectionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION()
	static bool SphereToSphereIntersection(const FVector& SphereCenter1, const float SphereRadius1, const FVector& SphereCenter2, const float SphereRadius2)
	{
		const float DistanceSquared = FVector::DistSquared(SphereCenter1, SphereCenter2);
		const float SumOfRadiiSquared = FMath::Square(SphereRadius1 + SphereRadius2);

		return DistanceSquared <= SumOfRadiiSquared;
	}

	UFUNCTION()
	static bool AABBIntersection(const FVector& MinA, const FVector& MaxA, const FVector& MinB, const FVector& MaxB)
	{
		if(MinA.X > MaxB.X || MinB.X > MaxA.X)
			return false;

		if(MinA.Y > MaxB.Y || MinB.Y > MaxA.Y)
			return false;

		if(MinA.Z > MaxB.Z || MinB.Z > MaxA.Z)
			return false;

		return true;
	}

	UFUNCTION()
	static bool SphereToAABBIntersection(const FVector& SphereCenter, const float SphereRadius, const FVector& Min, const FVector& Max)
	{
		const auto ClosestPoint = FVector(
			FMath::Clamp(SphereCenter.X, Min.X, Max.X),
			FMath::Clamp(SphereCenter.Y, Min.Y, Max.Y),
			FMath::Clamp(SphereCenter.Z, Min.Z, Max.Z)
		);

		const auto Distance = FVector::Dist(SphereCenter, ClosestPoint);
		return Distance <= SphereRadius;
	}
};
