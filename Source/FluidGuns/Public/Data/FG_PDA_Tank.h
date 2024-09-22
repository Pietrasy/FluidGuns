// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "FG_PDA_Item.h"
#include "Structures/FG_FTankParameters.h"
#include "FG_PDA_Tank.generated.h"

/**
 * Class for tank data assets.
 */
UCLASS()
class FLUIDGUNS_API UFG_PDA_Tank : public UFG_PDA_Item
{
	GENERATED_BODY()

public:
	// Base structure for tank.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Tank")
	FTankParameters TankParameters;

private:
	/*
	 * Function is called only during first PIE.
	 * In order for PostLoad() to be called for newly created data asset, restart of the engine is required.
	 */
	virtual void PostLoad() override;
};
