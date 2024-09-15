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
	virtual void PostLoad() override;
};
