// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FG_AddonInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UFG_AddonInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to work with addon components.
 */
class FLUIDGUNS_API IFG_AddonInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangePressureLevel(UPARAM(ref)float& Pressure, const float MaxPressure);
};