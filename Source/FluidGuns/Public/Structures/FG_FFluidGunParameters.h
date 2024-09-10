#pragma once

#include "FG_FFluidGunParameters.generated.h"

USTRUCT(BlueprintType)
struct FFluidGunParameters
{
	GENERATED_BODY()

	// Multiplied by BaseRange determines Range.
	UPROPERTY(BlueprintReadOnly)
	float Pressure = 0.f;
	
	// Maximum Pressure value for fluid gun.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxPressure = 0.f;
	
	// Resulting value from multiplication of Pressure and BaseRange.
	UPROPERTY(BlueprintReadOnly)
	float Range = 0.f;
	
	// Multiplied by Pressure determines Range.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseRange = 0.f;
	
	// Firing frequency.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FireRate = 0.f;
};
