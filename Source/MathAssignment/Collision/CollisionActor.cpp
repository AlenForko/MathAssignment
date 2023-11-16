#include "CollisionActor.h"

ACollisionActor::ACollisionActor()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ACollisionActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACollisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

