// Copyright Pietras


#include "Actions/FG_AddFluidGunAction.h"

#include "Characters/FG_Player.h"
#include "Data/FG_PDA_FluidGun.h"
#include "Interfaces/FG_ActionInterface.h"

void UFG_AddFluidGunAction::Execute_Implementation(UFG_PDA_Item* Item, AFG_Player* Player)
{
	Super::Execute_Implementation(Item, Player);

	// Check if data asset is fluid gun's data.
	FluidGun = CastChecked<UFG_PDA_FluidGun>(Item);
	// Call interface function.
	IFG_ActionInterface::Execute_AddGun(Player, FluidGun);
}
