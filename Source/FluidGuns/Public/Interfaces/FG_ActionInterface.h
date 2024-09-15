// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FG_ActionInterface.generated.h"

class UFG_PDA_Tank;
class UFG_PDA_FluidGun;
// This class does not need to be modified.
UINTERFACE()
class UFG_ActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for handling overriden Execute() functions of actions.
 */
class FLUIDGUNS_API IFG_ActionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void AddGun(const UFG_PDA_FluidGun* FluidGunDA);
	
	UFUNCTION(BlueprintNativeEvent)
	void AddTank(const UFG_PDA_Tank* TankDA);
};
