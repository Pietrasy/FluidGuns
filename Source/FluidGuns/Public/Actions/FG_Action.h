// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FG_Action.generated.h"

class AFG_Player;
class UFG_PDA_Item;

/**
 * Action is "lambda" in data assets that calls Execute() function which can be overridden.
 */
UCLASS(EditInlineNew, BlueprintType, Blueprintable)
class FLUIDGUNS_API UFG_Action : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Execute(UFG_PDA_Item* Item, AFG_Player* Player);
};
