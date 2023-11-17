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
	static bool SphereToSphereIntersection(const FVector& SphereCenter1, const float SphereRadius1, const FVector& SphereCenter2, const float SphereRadius2, FVector& ContactPoint)
	{
		const float DistanceSquared = FVector::DistSquared(SphereCenter1, SphereCenter2);
		const float SumOfRadiiSquared = FMath::Square(SphereRadius1 + SphereRadius2);

		const bool bIntersects = DistanceSquared <= SumOfRadiiSquared;

		if(bIntersects)
		{
			const auto Direction = SphereCenter2 - SphereCenter1;
			RaySphere(SphereCenter1, Direction.GetSafeNormal(), SphereCenter2, SphereRadius2, ContactPoint);
		}

		return bIntersects;
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

	UFUNCTION()
	static bool RaySphere(const FVector Origin, const FVector Direction, const FVector Center, const float Radius, FVector& ContactPoint)
	{
		const auto W = Center - Origin;
		const double WSQ = W.Dot(W);
		const double Projection = W.Dot(Direction);
		const float RSQ = Radius * Radius;

		// If sphere is behind ray, no intersection
		if(Projection < 0.f && WSQ > RSQ)
			return false;

		const double VSQ = Direction.Dot(Direction);

		// Diff vs radius
		const bool bIntersects = (VSQ * WSQ - Projection * Projection <= VSQ * Radius * Radius);

		if(bIntersects)
		{
			const double B = 2.f * Projection;
			const double C = WSQ - Radius * Radius;
			const double Discriminant = B * B - 4 * VSQ * C;
			const double T = (B - FMath::Sqrt(Discriminant)) / (2.f * VSQ);

			if(Discriminant < 0)
				ContactPoint = Origin + (Direction * -1.f);
			else
				ContactPoint = Origin + (Direction * T);
		}
		
		return bIntersects;
	}
};
