// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "FG_PDA_Item.generated.h"

/**
 * Base class of item's data assets.
 */
UCLASS(Abstract)
class FLUIDGUNS_API UFG_PDA_Item : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// Static mesh for item.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ItemProperties")
	TObjectPtr<UStaticMesh> ItemStaticMesh = nullptr;

	// Gameplay tag for item.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ItemProperties")
	FGameplayTag ItemGameplayTag = FGameplayTag::EmptyTag;

	// Name for item.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ItemProperties")
	FName ItemName = "Item";
};
