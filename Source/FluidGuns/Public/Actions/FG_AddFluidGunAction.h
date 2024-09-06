// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "FG_Action.h"
#include "FG_AddFluidGunAction.generated.h"

class UFG_PDA_FluidGun;

/**
 * Passes fluid gun to player, if player implements interface.
 */
UCLASS()
class FLUIDGUNS_API UFG_AddFluidGunAction : public UFG_Action
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation(UFG_PDA_Item* Item, AFG_Player* Player) override;

private:
	TObjectPtr<UFG_PDA_FluidGun> FluidGun = nullptr;
};
