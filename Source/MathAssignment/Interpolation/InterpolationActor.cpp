// Fill out your copyright notice in the Description page of Project Settings.


#include "InterpolationActor.h"

// Sets default values
AInterpolationActor::AInterpolationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMeshComponent);
}

// Called every frame
void AInterpolationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!IsValid(CurveFloat)) return;

	Time += DeltaTime;

	float T = Time / Duration;

	float Value = CurveFloat->FloatCurve.Eval(T);
	
	if(IsLerpTypeSelected(ELerpType::LerpScale))
	{
		SetActorScale3D(FVector(Value, Value, Value));
	}
	if(IsLerpTypeSelected(ELerpType::LerpRotate))
	{
		SetActorRotation(FRotator(0, 360 * Value, 0));
	}
	if(IsLerpTypeSelected(ELerpType::LerpUpDown))
	{
		SetActorLocation(FVector(0, 0, 1000 * Value));
	}
	if(T >= 1)
	{
		Time = 0;
	}
	
}

bool AInterpolationActor::ShouldTickIfViewportsOnly() const
{
	return true;
}

bool AInterpolationActor::IsLerpTypeSelected(ELerpType InLerpType) const
{
	int32 LerpIndex = static_cast<int32>(InLerpType);
	return SelectedLerps.IsValidIndex(LerpIndex) && SelectedLerps[LerpIndex];
}

