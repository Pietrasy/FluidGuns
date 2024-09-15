// Copyright Pietras

#pragma once

#include "Components/FG_Addon.h"
#include "Structures/FG_FFluidGunParameters.h"
#include "GameplayTags.h"

#include "FG_FFluidGunProperties.generated.h"

class UFG_PDA_Tank;
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

	// Last tank that was attached to fluid gun.
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag CurrentTank = FGameplayTag::EmptyTag;

	// Whether fluid fun has own tank.
	UPROPERTY(BlueprintReadWrite)
	bool bHasOwnTank = false;

	// Operator overloading for comparing this structure.
	bool operator==(const FFluidGunProperties& RHS) const {return FluidGunGameplayTag == RHS.FluidGunGameplayTag;}
};

