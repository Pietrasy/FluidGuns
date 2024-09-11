// Copyright Pietras


#include "Components/FG_Addon.h"

UFG_Addon::UFG_Addon()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Set collision profile.
	UStaticMeshComponent::SetCollisionProfileName("NoCollision", false);
}
