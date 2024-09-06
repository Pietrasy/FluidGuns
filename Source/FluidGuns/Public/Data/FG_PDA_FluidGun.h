// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "FG_PDA_Item.h"
#include "FG_PDA_FluidGun.generated.h"

USTRUCT(BlueprintType)
struct FFluidGunData
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

/**
 * Class for fluid gun's data assets.
 */
UCLASS()
class FLUIDGUNS_API UFG_PDA_FluidGun : public UFG_PDA_Item
{
	GENERATED_BODY()

public:
	// Base structure for fluid gun.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FluidGun")
	FFluidGunData FluidGunData;
};
