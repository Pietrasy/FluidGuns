#pragma once

#include "FG_FTankParameters.h"
#include "GameplayTagContainer.h"
#include "FG_FTankProperties.generated.h"

USTRUCT(BlueprintType)
struct FTankProperties
{
	GENERATED_BODY()
	// Base structure for tank.
	UPROPERTY(BlueprintReadWrite)
	FTankParameters TankData;

	// Tank static mesh.
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* StaticMesh = nullptr;

	// Gameplay Tag for tank.
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag GameplayTag = FGameplayTag::EmptyTag;

	// Name of tank.
	UPROPERTY(BlueprintReadWrite)
	FName Name;

	bool operator==(const FTankProperties& RHS) const {return GameplayTag == RHS.GameplayTag;}
};