// Fill out your copyright notice in the Description page of Project Settings.


#include "StateActor.h"
#include "Components/TextRenderComponent.h"
#include "MathAssignment/ContextLibrary.h"

// Sets default values
AStateActor::AStateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMeshComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("Text");
	TextRenderComponent->SetupAttachment(StaticMeshComponent);
}

// Called every frame
void AStateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (const auto OtherActor : OtherActors)
	{
		if(OtherActor == nullptr)continue;
		
		FString Value;
		int32 GameContext = UContextLibrary::CalculateWorldLocation(this, OtherActor);

		bool bInFront = (GameContext & static_cast<int32>(WorldLocation::Infront)) != 0;
		bool bBehind = (GameContext & static_cast<int32>(WorldLocation::Behind)) != 0;
		bool bAbove = (GameContext & static_cast<int32>(WorldLocation::Above)) != 0;
		bool bUnderneath = (GameContext & static_cast<int32>(WorldLocation::Underneath)) != 0;
		bool bLeft = (GameContext & static_cast<int32>(WorldLocation::Left)) != 0;
		bool bRight = (GameContext & static_cast<int32>(WorldLocation::Right)) != 0;
		bool bFar = (GameContext & static_cast<int32>(WorldLocation::Far)) != 0;
		bool bNear = (GameContext & static_cast<int32>(WorldLocation::Near)) != 0;
		
		if(bInFront)
		{
			Value = "in front";
		}
		else if(bBehind)
		{
			Value = "behind";
		}

		if(bAbove)
		{
			Value += ", above";
		}
		else if(bUnderneath)
		{
			Value += ", underneath";
		}

		if(bLeft)
		{
			Value += ", to the left";
		}
		else if(bRight)
		{
			Value += ", to the right";
		}

		if(bNear)
		{
			Value += " & near.";
		}
		else if(bFar)
		{
			Value += " & far.";
		}
		
		UTextRenderComponent* TextRenderers = OtherActor->FindComponentByClass<UTextRenderComponent>();

		TextRenderers->SetText(FText::FromString("The actor is " + Value));
	}
}

bool AStateActor::ShouldTickIfViewportsOnly() const
{
	return true;
}

