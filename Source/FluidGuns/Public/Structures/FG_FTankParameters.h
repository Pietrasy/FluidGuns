#pragma once

#include "FG_FTankParameters.generated.h"

USTRUCT(BlueprintType)
struct FTankParameters
{
	GENERATED_BODY()

	// Amount of fluid in tank.
	UPROPERTY(BlueprintReadWrite)
	float FluidAmount = 0;

	// Max amount of fluid in tank.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxFluidAmount = 0;
};
