// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/FG_AddonInterface.h"
#include "FG_Addon.generated.h"

/**
 * Base class of fluid gun's addons.
 */
UCLASS(Abstract)
class FLUIDGUNS_API UFG_Addon : public UStaticMeshComponent,  public IFG_AddonInterface
{
	GENERATED_BODY()

public:
	UFG_Addon();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Addon")
	FGameplayTag AddonTag = FGameplayTag::EmptyTag;
};