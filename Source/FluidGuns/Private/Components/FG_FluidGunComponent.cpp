// Copyright Pietras


#include "Components/FG_FluidGunComponent.h"

// Sets default values for this component's properties
UFG_FluidGunComponent::UFG_FluidGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UFG_FluidGunComponent::AddFluidGun(const UFG_PDA_FluidGun* FluidGunDA)
{
	for (FFluidGun& FluidGun : OwnedGuns)
	{
		// Check if gun is already in array.
		if (!FluidGun.FluidGunGameplayTag.MatchesTag(FluidGun.FluidGunGameplayTag))
		{
			// Copy data from fluid gun's data asset and cache its in component's structure.
			FluidGun.FluidGunData = FluidGunDA->FluidGunData;
			FluidGun.StaticMesh = FluidGunDA->ItemStaticMesh;
			FluidGun.FluidGunGameplayTag = FluidGunDA->ItemGameplayTag;
			FluidGun.FluidGunName = FluidGunDA->ItemName;
		}
		else
		{
			return;
		}

		// Add structure to array.
		OwnedGuns.Add(FluidGun);
	}
}
