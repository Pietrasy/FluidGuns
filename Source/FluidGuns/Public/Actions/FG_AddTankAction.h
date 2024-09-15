// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "FG_Action.h"
#include "FG_AddTankAction.generated.h"

class UFG_PDA_Tank;
/**
 * Passes tank to player, if player implements interface.
 */
UCLASS()
class FLUIDGUNS_API UFG_AddTankAction : public UFG_Action
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation(UFG_PDA_Item* Item, AFG_Player* Player) override;

private:
	TObjectPtr<UFG_PDA_Tank> Tank = nullptr;
};
