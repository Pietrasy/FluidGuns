// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "Structures/FG_FTankProperties.h"
#include "UObject/Object.h"
#include "FG_WidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGunUpdate_WidgetSignature, float, Pressure, float, MaxPressure);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTankUpdate_WidgetSignature, float, FluidAmount, float, MaxFluidAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowSelectTankWidgetSignature, const TArray<FTankProperties>&, Tanks);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectTankSignature, FGameplayTag, TankTag);

/**
 *  WidgetController is proxy between HUD and Widgets of FG_BaseWidget class.
 */
UCLASS()
class FLUIDGUNS_API UFG_WidgetController : public UObject
{
	GENERATED_BODY()

public:
	// Fluid gun data to update its widget.
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGunUpdate_WidgetSignature OnGunUpdate;

	// Tank data to update its widget.
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTankUpdate_WidgetSignature OnTankUpdate;

	// Call at start selector tank widget and pass data to it.
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnShowSelectTankWidgetSignature OnShowSelectTankWidget;

	// Retrieve tank tag from selector tank widget.
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSelectTankSignature OnSelectTank;
};
