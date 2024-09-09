// Copyright Pietras


#include "Actors/FG_FluidGun.h"

AFG_FluidGun::AFG_FluidGun()
{
	// Create static mesh component, set it as root and set its collision profile.
	FluidGunStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("FluidGunStaticMesh");
	SetRootComponent(FluidGunStaticMesh);
	FluidGunStaticMesh->SetCollisionProfileName("NoCollision", false);
}

void AFG_FluidGun::UpdateGun(const FG_FFluidGunStructure& FluidGun)
{
	FluidGunProperties = FluidGun;
	FluidGunName = FluidGun.FluidGunName;
	FluidGunGameplayTag = FluidGun.FluidGunGameplayTag;
	FluidGunStaticMesh->SetStaticMesh(FluidGun.StaticMesh);
}
