// Copyright Pietras


#include "Data/FG_PDA_Tank.h"

void UFG_PDA_Tank::PostLoad()
{
	Super::PostLoad();

	TankParameters.FluidAmount = TankParameters.MaxFluidAmount;
}
