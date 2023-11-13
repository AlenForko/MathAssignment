// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterpolationActor.generated.h"

UENUM(BlueprintType)
enum class ELerpType : uint8
{
	LerpScale,
	LerpRotate,
	LerpUpDown
};

UCLASS()
class MATHASSIGNMENT_API AInterpolationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterpolationActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual bool ShouldTickIfViewportsOnly() const override;
protected:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;

	float Time = 0;
	
	UPROPERTY(EditAnywhere)
	float Duration = 1;

	UPROPERTY(EditAnywhere)
	TArray<bool> SelectedLerps;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ELerpType> LerpType;

	UFUNCTION()
	bool IsLerpTypeSelected(ELerpType InLerpType) const;
};
