// Copyright Pietras


#include "Actions/FG_AddTankAction.h"

#include "Characters/FG_Player.h"
#include "Data/FG_PDA_Tank.h"
#include "Interfaces/FG_ActionInterface.h"

void UFG_AddTankAction::Execute_Implementation(UFG_PDA_Item* Item, AFG_Player* Player)
{
	Super::Execute_Implementation(Item, Player);
	
	// Check if data asset is fluid gun's data.
	Tank = CastChecked<UFG_PDA_Tank>(Item);
	// Call interface function.
	IFG_ActionInterface::Execute_AddTank(Player, Tank);
}
