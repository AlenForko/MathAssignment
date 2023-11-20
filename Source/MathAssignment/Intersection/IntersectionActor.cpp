#include "IntersectionActor.h"

#include "IntersectionSubsystem.h"

AIntersectionActor::AIntersectionActor()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AIntersectionActor::BeginPlay()
{
	Super::BeginPlay();

	const auto SubSystem = GetWorld()->GetSubsystem<UIntersectionSubsystem>();
	SubSystem->RegisterActor(this);
}

void AIntersectionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DebugDrawShape();
	ShapeColor = FColor::Green;
}

bool AIntersectionActor::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AIntersectionActor::DebugDrawShape() const
{
	switch (IntersectionType.GetValue())
	{
	case EIntersectionType::Sphere:
		DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 32, ShapeColor, false, -1, 1, 0.5);
		break;
		
	case EIntersectionType::AABB:
		DrawDebugBox(GetWorld(), GetActorLocation(), BoxSize, ShapeColor, false, -1, 1, 0.5f);
		break;
		
	default: ;
	}
}

void AIntersectionActor::HandleCollisionResponse(AIntersectionActor* OtherActor, const FVector& ContactPoint)
{
	FVector CollisionNormal = -(OtherActor->GetActorLocation() - ContactPoint).GetSafeNormal();
	Velocity = FMath::GetReflectionVector(Velocity, CollisionNormal);
	
	UE_LOG(LogTemp, Warning, TEXT("CollisionNormal: %s"), *CollisionNormal.ToString());
	UE_LOG(LogTemp, Warning, TEXT("New Velocity: %s"), *Velocity.ToString());
}
