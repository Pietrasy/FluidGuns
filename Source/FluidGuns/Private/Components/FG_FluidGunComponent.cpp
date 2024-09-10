// Copyright Pietras


#include "Components/FG_FluidGunComponent.h"

#include "Actors/FG_FluidGun.h"
#include "Characters/FG_Player.h"

void UFG_FluidGunComponent::BeginPlay()
{
	// Get owner of this component and set as PlayerCharacter.
	PlayerCharacter = CastChecked<AFG_Player>(GetOwner());
	
	Super::BeginPlay();
}

void UFG_FluidGunComponent::AddFluidGun(const UFG_PDA_FluidGun* FluidGunDA)
{
	for (FG_FFluidGunStructure& FluidGun : OwnedGuns)
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

		// Add fluid gun's structure to array.
		OwnedGuns.Add(FluidGun);
	}
}

void UFG_FluidGunComponent::DrawFluidGun(const FG_FFluidGunStructure& FluidGun)
{
	// Check if given gun isn't the same as CurrentGun.
	if(!CurrentGun->FluidGunGameplayTag.MatchesTag(FluidGun.FluidGunGameplayTag))
	{
		// Overwrite fluid gun's data. 
		CurrentGun->UpdateGun(FluidGun);
		OnGunUpdate.Broadcast(FluidGun.FluidGunData.Pressure, FluidGun.FluidGunData.MaxPressure);
	}
}
