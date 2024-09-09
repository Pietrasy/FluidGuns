// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/FG_PDA_FluidGun.h"
#include "Structures/FG_FFluidGunStructure.h"
#include "FG_FluidGunComponent.generated.h"

class AFG_FluidGun;

UCLASS(Blueprintable)
class FLUIDGUNS_API UFG_FluidGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFG_FluidGunComponent();

	// Adds picked up fluid gun to OwnedGuns array.
	UFUNCTION(BlueprintCallable)
	void AddFluidGun(const UFG_PDA_FluidGun* FluidGunDA);

	// 
	UFUNCTION(BlueprintCallable)
	void DrawFluidGun(const FG_FFluidGunStructure& FluidGun);

private:
	// Array of player's fluid guns.
	UPROPERTY(BlueprintReadOnly, Category="Component|FluidGun", meta=(AllowPrivateAccess))
	TArray<FG_FFluidGunStructure> OwnedGuns;

	// Currently draw gun.
	UPROPERTY(BlueprintReadWrite, Category="Component|FluidGun", meta=(AllowPrivateAccess))
	TObjectPtr<AFG_FluidGun> CurrentGun = nullptr;
};
