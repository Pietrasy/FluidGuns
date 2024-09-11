// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "FG_PDA_Item.h"
#include "Structures/FG_FFluidGunParameters.h"
#include "FG_PDA_FluidGun.generated.h"

class UFG_Addon;
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
	FFluidGunParameters FluidGunData;

	// Array of addons for fluid gun.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FLuidGun")
	TArray<TSubclassOf<UFG_Addon>> Addons;

private:
	virtual void PostLoad() override;
};
