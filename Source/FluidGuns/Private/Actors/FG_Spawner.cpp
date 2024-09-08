// Copyright Pietras


#include "Actors/FG_Spawner.h"

#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AFG_Spawner::AFG_Spawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CreateAndAttachComponent();
}

void AFG_Spawner::CreateAndAttachComponent()
{
	// Create sphere component and set it as root.
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereCollision);

	// Create static mesh component and attach it to sphere component.
	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	ItemStaticMesh->SetupAttachment(SphereCollision);

	// Create arrow component and attach it to sphere component.
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(SphereCollision);
}





