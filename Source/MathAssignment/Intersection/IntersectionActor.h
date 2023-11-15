// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IntersectionActor.generated.h"

class USphereComponent;
UCLASS()
class MATHASSIGNMENT_API AIntersectionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIntersectionActor();
	
	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override;
	
protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;
	
	UPROPERTY(EditAnywhere)
	AIntersectionActor* OtherSphereActor;
	
};
