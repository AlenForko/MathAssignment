// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ContextLibrary.generated.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class WorldLocation : uint8
{
	NONE = 0,
	Infront = 1 << 0,
	Behind = 1 << 1,
	Above = 1 << 2,
	Underneath = 1 << 3,
	Left = 1 << 4,
	Right = 1 << 5,
	Near = 1 << 6,
	Far = 1 << 7
};

UCLASS()
class MATHASSIGNMENT_API UContextLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static int32 CalculateWorldLocation(AActor* MainActor, AActor* OtherActor)
	{
		int32 ContextFlags = 0;

		const float Range = 500;
		const FVector MyLocation = MainActor->GetActorLocation();
		const FVector OtherActorLocation = OtherActor->GetActorLocation();
		const FVector Direction = MyLocation - OtherActorLocation;
		
		const FVector LocalSpace = MainActor->GetActorTransform().InverseTransformPosition(OtherActorLocation);

		if(LocalSpace.X > 0)
		{
			ContextFlags |= static_cast<int32>(WorldLocation::Infront);
		}
		else if(LocalSpace.X < 0)
		{
			ContextFlags |= static_cast<int32>(WorldLocation::Behind);
		}

		if(LocalSpace.Y > 0)
		{
			ContextFlags |= static_cast<int32>(WorldLocation::Right);
		}
		else if(LocalSpace.Y < 0)
		{
			ContextFlags |= static_cast<int32>(WorldLocation::Left);
		}

		if(LocalSpace.Z > 0)
		{
			ContextFlags |= static_cast<int32>(WorldLocation::Above);
		}
		else if(LocalSpace.Z < 0)
		{
			ContextFlags |= static_cast<int32>(WorldLocation::Underneath);
		}

		if(Direction.Size() > Range)
		{
			ContextFlags |= static_cast<int32>(WorldLocation::Far);
		}
		else if(Direction.Size() < Range)
		{
			ContextFlags |= static_cast<int32>(WorldLocation::Near);
		}
		
		return ContextFlags;
	}	
};
