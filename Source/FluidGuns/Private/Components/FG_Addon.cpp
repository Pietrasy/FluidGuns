// Copyright Pietras


#include "Components/FG_Addon.h"

UFG_Addon::UFG_Addon()
{
	// Actor will not call Tick() every frame.
	PrimaryComponentTick.bCanEverTick = false;

	// Set collision profile.
	UStaticMeshComponent::SetCollisionProfileName("NoCollision", false);
}
