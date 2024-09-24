// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "Structures/FG_FTankProperties.h"
#include "UObject/Object.h"
#include "FG_WidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDrawFluidGunWidgetSignature, float, MaxPressure, bool, bIsPressureConst);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTankUpdateWidgetSignature, float, FluidAmount, float, MaxFluidAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateWidgetSignature, float, Pressure, float, Fluid);
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
	// Pass information about maximum pressure level and whether fluid gun pressure is constant.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="WidgetController|Delegate")
	FOnDrawFluidGunWidgetSignature OnDrawFluidGun;

	// Pass information about fluid amount of tank and it maximum fluid amount. 
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="WidgetController|Delegate")
	FOnTankUpdateWidgetSignature OnTankUpdate;

	// Called at the start of selector tank widget to provide it with data on available tanks.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="WidgetController|Delegate")
	FOnShowSelectTankWidgetSignature OnShowSelectTankWidget;

	// Retrieve tank tag from selector tank widget.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="WidgetController|Delegate")
	FOnSelectTankSignature OnSelectTank;

	// Pass information about pressure level and fluid amount.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="WidgetController|Delegate")
	FOnUpdateWidgetSignature OnParamsUpdate;
};
