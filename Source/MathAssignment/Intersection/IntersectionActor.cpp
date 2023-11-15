#include "IntersectionActor.h"

#include "Components/SphereComponent.h"

AIntersectionActor::AIntersectionActor()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(RootComponent);
}

void AIntersectionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Sphere1Center = GetActorLocation();
	float Sphere1Radius = SphereComponent->GetScaledSphereRadius();

	FVector Sphere2Center = OtherSphereActor->GetActorLocation();
	float Sphere2Radius = OtherSphereActor->SphereComponent->GetScaledSphereRadius();

	float DistanceSquared = FVector::DistSquared(Sphere1Center, Sphere2Center);
	float SumOfRadiiSquared = FMath::Square(Sphere1Radius + Sphere2Radius);

	bool bIntersects = DistanceSquared <= SumOfRadiiSquared;
	
	if (bIntersects)
	{
		UE_LOG(LogTemp, Warning, TEXT("Intersecting!"));
		DrawDebugSphere(GetWorld(), GetActorLocation(), SphereComponent->GetScaledSphereRadius(), 32, FColor::Red, false, 5, 1, 1);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Intersecting!"));
		DrawDebugSphere(GetWorld(), GetActorLocation(), SphereComponent->GetScaledSphereRadius(), 32, FColor::Green, false, 5, 1, 0.5);
	}
}

bool AIntersectionActor::ShouldTickIfViewportsOnly() const
{
	return true;
}
