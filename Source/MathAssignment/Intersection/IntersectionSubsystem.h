// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "IntersectionSubsystem.generated.h"

class AIntersectionActor;

UCLASS()
class MATHASSIGNMENT_API UIntersectionSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;
	void RegisterActor(AIntersectionActor* Actor);
	
protected:
	UPROPERTY()
	TArray<AIntersectionActor*> IntersectionActors;
};
