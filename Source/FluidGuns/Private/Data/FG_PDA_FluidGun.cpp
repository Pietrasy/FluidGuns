// Copyright Pietras


#include "Data/FG_PDA_FluidGun.h"

void UFG_PDA_FluidGun::PostLoad()
{
	Super::PostLoad();
	// Set Pressure with MaxPressure value.
	FluidGunData.Pressure = FluidGunData.MaxPressure;
}
