// Fill out your copyright notice in the Description page of Project Settings.


#include "InterpolationActor.h"

// Sets default values
AInterpolationActor::AInterpolationActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMeshComponent);

	for (int32 i = 0; i <= static_cast<int32>(ELerpType::LerpUpDown); ++i)
	{
		ELerpType LerpEnum = static_cast<ELerpType>(i);
		SelectedLerps.Add(LerpEnum, false);
	}
	
	LerpTypeNames.Add(ELerpType::LerpScale, FName("LerpScale"));
	LerpTypeNames.Add(ELerpType::LerpRotate, FName("LerpRotate"));
	LerpTypeNames.Add(ELerpType::LerpUpDown, FName("LerpUpDown"));
}

// Called every frame
void AInterpolationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!IsValid(CurveFloat)) return;

	Time += DeltaTime;

	float T = Time / Duration;

	float Value = CurveFloat->FloatCurve.Eval(T);
	
	for (const auto& Pair : LerpTypeNames)
	{
		ELerpType LerpEnum = Pair.Key;

		if (IsLerpTypeSelected(LerpEnum))
		{
			if (LerpEnum == ELerpType::LerpScale)
			{
				SetActorScale3D(FVector(Value, Value, Value));
			}
			else if (LerpEnum == ELerpType::LerpRotate)
			{
				SetActorRotation(FRotator(0, RotationValue * Value, 0));
			}
			else if (LerpEnum == ELerpType::LerpUpDown)
			{
				SetActorLocation(FVector(0, 0, UpDownValue * Value));
			}
		}
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
	const bool* bSelected = SelectedLerps.Find(InLerpType);
	return bSelected ? *bSelected : false;
}

