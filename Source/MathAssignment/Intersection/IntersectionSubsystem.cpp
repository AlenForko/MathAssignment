// Fill out your copyright notice in the Description page of Project Settings.


#include "IntersectionSubsystem.h"
#include "IntersectionActor.h"
#include "IntersectionLibrary.h"
#include "MathAssignment/Collision/CollisionActor.h"

void UIntersectionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UIntersectionSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	for (const auto ActorA : IntersectionActors)
	{
		ActorA->SetActorLocation(ActorA->GetActorLocation() + ActorA->Velocity * DeltaTime);
		
		for(const auto ActorB : IntersectionActors)
		{
			if(ActorA == ActorB) continue;
			
			if(ActorA->IntersectionType == EIntersectionType::Sphere &&
				ActorB->IntersectionType == EIntersectionType::Sphere)
			{
				FVector ContactPoint;
				if(UIntersectionLibrary::SphereToSphereIntersection(
					ActorA->GetActorLocation(),
					ActorA->SphereRadius,
					ActorB->GetActorLocation(),
					ActorB->SphereRadius,
					ContactPoint))
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						40.f,
						FColor::Black
						);
					
					DrawDebugLine(GetWorld(),
						ActorA->GetActorLocation(),
						ActorB->GetActorLocation(),
						FColor::Black,
						false,
						-1,
						0,
						2);
					
					ActorA->ShapeColor = FColor::Red;
					ActorB->ShapeColor = FColor::Red;
					ActorA->HandleCollisionResponse(ActorB, ContactPoint);
				}
			}

			if(ActorA->IntersectionType == EIntersectionType::AABB && ActorB->IntersectionType == EIntersectionType::AABB)
			{
				if(UIntersectionLibrary::AABBIntersection(
				ActorA->GetActorLocation() - ActorA->BoxSize,
				ActorA->BoxSize + ActorA->GetActorLocation(),
				ActorB->GetActorLocation() - ActorB->BoxSize,
				ActorB->BoxSize + ActorB->GetActorLocation()))
				{
					ActorA->ShapeColor = FColor::Red;
					ActorB->ShapeColor = FColor::Red;
				}
			}

			if(ActorA->IntersectionType == EIntersectionType::Sphere && ActorB->IntersectionType == EIntersectionType::AABB)
			{
				if(UIntersectionLibrary::SphereToAABBIntersection(
					ActorA->GetActorLocation(),
					ActorA->SphereRadius,
					ActorB->GetActorLocation() - ActorB->BoxSize,
					ActorB->GetActorLocation() + ActorB->BoxSize))
				{
					ActorA->ShapeColor = FColor::Red;
					ActorB->ShapeColor = FColor::Red;
				}
			}
		}
	}
}

TStatId UIntersectionSubsystem::GetStatId() const
{
	return TStatId();
}

void UIntersectionSubsystem::RegisterActor(AIntersectionActor* Actor)
{
	if(IntersectionActors.Contains(Actor))return;
	IntersectionActors.Add(Actor);
}


