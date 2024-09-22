// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "FG_PDA_Item.generated.h"

class UFG_Action;

/**
 * Base class of item's data assets.
 */
UCLASS(Abstract)
class FLUIDGUNS_API UFG_PDA_Item : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ItemProperties")
	TObjectPtr<UStaticMesh> ItemStaticMesh = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ItemProperties")
	FGameplayTag ItemGameplayTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ItemProperties")
	FName ItemName = "Item";

	// What action will be call after pick up item.
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category= "Actions")
	TObjectPtr<UFG_Action> Action = nullptr;
};
