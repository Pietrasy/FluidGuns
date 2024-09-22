// Copyright Pietras


#include "Actors/FG_FluidSource.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

AFG_FluidSource::AFG_FluidSource()
{
	// Create sphere component, set it as root component.
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);
	// Create fluid source static mesh component and attach it to sphere collision component.
	FluidSourceStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("FluidSourceStaticMesh");
	FluidSourceStaticMesh->SetupAttachment(SphereCollision);
	// Create widget component and attach it to fluid source static mesh component.
	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("InteractionWidget");
	InteractionWidgetComponent->SetupAttachment(FluidSourceStaticMesh);
}
