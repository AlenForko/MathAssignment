#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollisionActor.generated.h"

UCLASS()
class MATHASSIGNMENT_API ACollisionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollisionActor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
};
