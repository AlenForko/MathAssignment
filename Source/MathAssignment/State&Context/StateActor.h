// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateActor.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;
UCLASS()
class MATHASSIGNMENT_API AStateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AStateActor();

	virtual bool ShouldTickIfViewportsOnly() const override;

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* TextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> OtherActors;

	UPROPERTY(BlueprintReadWrite, meta=(Bitmask, BitmaskEnum = "/Script/MathCourse.WorldLocation"))
	int32 Context;
};
