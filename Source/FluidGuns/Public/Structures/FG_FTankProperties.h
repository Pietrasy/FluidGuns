#pragma once

#include "FG_FTankParameters.h"
#include "GameplayTags.h"
#include "FG_FTankProperties.generated.h"

USTRUCT(BlueprintType)
struct FTankProperties
{

	GENERATED_BODY()

	// Base structure for tank.
	UPROPERTY(BlueprintReadWrite)
	FTankParameters TankData;

	// Static mesh for tank.
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* StaticMesh = nullptr;

	// Gameplay Tag for tank.
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag GameplayTag = FGameplayTag::EmptyTag;

	// Name for tank.
	UPROPERTY(BlueprintReadWrite)
	FName Name;
};
