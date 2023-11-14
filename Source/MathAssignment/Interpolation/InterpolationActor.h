// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterpolationActor.generated.h"

UENUM(BlueprintType)
enum class ELerpType : uint8
{
	LerpScale UMETA(DisplayName = "Lerp Scale"),
	LerpRotate UMETA(DisplayName = "Lerp Rotate"),
	LerpUpDown UMETA(DisplayName = "Lerp Up-Down")
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
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere)
	float Duration = 1;
	
	float Time = 0;

	UPROPERTY(EditAnywhere)
	float UpDownValue;

	UPROPERTY(EditAnywhere)
	float RotationValue = 360;
	
	UPROPERTY(EditAnywhere, meta = (DisplayAfter))
	TMap<ELerpType, bool> SelectedLerps;
	
	UPROPERTY()
	ELerpType LerpType;

	UFUNCTION()
	bool IsLerpTypeSelected(ELerpType InLerpType) const;
	
	UPROPERTY()
	TMap<ELerpType, FName> LerpTypeNames;
};