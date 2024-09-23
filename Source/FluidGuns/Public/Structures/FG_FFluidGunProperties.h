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

	// Fluid gun static mesh.
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;

	// Fluid gun gameplay tag
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag FluidGunGameplayTag = FGameplayTag::EmptyTag;

	// Name of fluid gun.
	UPROPERTY(BlueprintReadWrite)
	FName FluidGunName;

	// Fluid gun addons.
	UPROPERTY(BlueprintReadWrite)
	TArray<TSubclassOf<UFG_Addon>> Addons;

	// Last tank that was attached to fluid gun.
	UPROPERTY(BlueprintReadWrite)
	TOptional<FGameplayTag> AttachedTank;
	
	// Indicates whether fluid gun has own tank.
	UPROPERTY(BlueprintReadWrite)
	bool bHasOwnTank = false;

	// Amount of fluid in own tank.
	UPROPERTY(BlueprintReadWrite)
	float OwnTankFluidAmount = 0.f;

	// Max Amount of fluid in own tank.
	UPROPERTY(BlueprintReadWrite)
	float OwnTankMaxFluidAmount = 0.f;

	// Indicates whether fluid gun pressure is constant. 
	UPROPERTY(BlueprintReadWrite)
	bool bConstPressure = false;

	// Operator overloading for comparing this structure.
	bool operator==(const FFluidGunProperties& RHS) const {return FluidGunGameplayTag == RHS.FluidGunGameplayTag;}
};

