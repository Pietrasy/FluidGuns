// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/FG_PDA_FluidGun.h"
#include "Structures/FG_FFluidGunStructure.h"
#include "FG_FluidGunComponent.generated.h"

class AFG_Player;
class AFG_FluidGun;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGunUpdateSignature, float, Pressure, float, MaxPressure);

UCLASS(Blueprintable)
class FLUIDGUNS_API UFG_FluidGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// Adds picked up fluid gun to OwnedGuns array.
	UFUNCTION(BlueprintCallable)
	void AddFluidGun(const UFG_PDA_FluidGun* FluidGunDA);

	// Draw fluid gun and set as CurrentGun.
	UFUNCTION(BlueprintCallable)
	void DrawFluidGun(const FG_FFluidGunStructure& FluidGun);

	// Fluid gun's data to update its widget.
	UPROPERTY(BlueprintAssignable)
	FOnGunUpdateSignature OnGunUpdate;

private:
	// Array of player's fluid guns.
	UPROPERTY(BlueprintReadOnly, Category="Component|FluidGun", meta=(AllowPrivateAccess))
	TArray<FG_FFluidGunStructure> OwnedGuns;

	// Currently draw gun.
	UPROPERTY(BlueprintReadWrite, Category="Component|FluidGun", meta=(AllowPrivateAccess))
	TObjectPtr<AFG_FluidGun> CurrentGun = nullptr;

	// Components' owner.
	UPROPERTY(BlueprintReadWrite, Category="Component|PlayerCharacter", meta=(AllowPrivateAccess))
	TObjectPtr<AFG_Player> PlayerCharacter = nullptr;
};
