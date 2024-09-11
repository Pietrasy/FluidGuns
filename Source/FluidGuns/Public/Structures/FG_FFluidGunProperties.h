// Copyright Pietras

#pragma once

#include "Structures/FG_FFluidGunParameters.h"
#include "GameplayTags.h"

#include "FG_FFluidGunProperties.generated.h"

class UFG_Addon;

USTRUCT(BlueprintType)
struct FFluidGunProperties
{
	GENERATED_BODY()

	// Base structure for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	FFluidGunParameters FluidGunData;

	// Static mesh for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;

	// Gameplay tag for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag FluidGunGameplayTag = FGameplayTag::EmptyTag;

	// Name for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	FName FluidGunName;

	// Addons for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	TArray<TSubclassOf<UFG_Addon>> Addons;
};
