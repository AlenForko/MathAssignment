// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IntersectionActor.generated.h"

UENUM(BlueprintType)
enum class EIntersectionType
{
	AABB,
	Sphere
};

class USphereComponent;
UCLASS()
class MATHASSIGNMENT_API AIntersectionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIntersectionActor();
	
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual bool ShouldTickIfViewportsOnly() const override;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EIntersectionType> IntersectionType;

	UPROPERTY(EditAnywhere)
	float SphereRadius = 32;

	FColor ShapeColor = FColor::Green;

	UPROPERTY(EditAnywhere)
	FVector Velocity = FVector::Zero();
	
	UPROPERTY(EditAnywhere)
	FVector BoxSize;

	virtual void DebugDrawShape() const;

	virtual void HandleCollisionResponse(AIntersectionActor* OtherActor, const FVector& ContactPoint);
};
