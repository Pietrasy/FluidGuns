// Copyright Pietras


#include "Data/FG_PDA_Tank.h"

void UFG_PDA_Tank::PostLoad()
{
	Super::PostLoad();
	// Set FluidAmount with MaxFluidAmount value.
	TankParameters.FluidAmount = TankParameters.MaxFluidAmount;
}
