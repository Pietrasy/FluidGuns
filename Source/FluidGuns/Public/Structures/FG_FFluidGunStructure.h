// Copyright Pietras

#pragma once

#include "Data/FG_PDA_FluidGun.h"

#include "FG_FFluidGunStructure.generated.h"

USTRUCT(BlueprintType)
struct FG_FFluidGunStructure
{
	GENERATED_BODY()

	// Base structure for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	FFluidGunData FluidGunData;

	// Static mesh for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;

	// Gameplay tag for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag FluidGunGameplayTag = FGameplayTag::EmptyTag;

	// Name for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	FName FluidGunName;
};
