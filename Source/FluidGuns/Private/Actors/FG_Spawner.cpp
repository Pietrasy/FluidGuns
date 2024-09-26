// Copyright Pietras


#include "Actors/FG_Spawner.h"

#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

AFG_Spawner::AFG_Spawner()
{
	// Actor will not call Tick() every frame.
	PrimaryActorTick.bCanEverTick = false;
	// Create sphere component and set it as root.
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereCollision);
	// Create static mesh component and attach it to sphere component.
	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	ItemStaticMesh->SetCollisionProfileName("NoCollision", false);
	ItemStaticMesh->SetupAttachment(SphereCollision);
	// Create arrow component and attach it to sphere component.
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(SphereCollision);
}