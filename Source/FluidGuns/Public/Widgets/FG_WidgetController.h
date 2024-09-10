// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FG_WidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGunUpdate_WidgetSignature, float, Pressure, float, MaxPressure);

/**
 *  WidgetController is proxy between HUD and Widgets.
 */
UCLASS()
class FLUIDGUNS_API UFG_WidgetController : public UObject
{
	GENERATED_BODY()

public:
	// Fluid gun's data to update its widget.
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGunUpdate_WidgetSignature OnGunUpdate;
};
