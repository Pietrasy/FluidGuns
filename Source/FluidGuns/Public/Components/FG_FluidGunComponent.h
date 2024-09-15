// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/FG_PDA_FluidGun.h"
#include "Structures/FG_FFluidGunProperties.h"
#include "Structures/FG_FTankProperties.h"
#include "FG_FluidGunComponent.generated.h"

class UFG_PDA_Tank;
class AFG_Player;
class AFG_FluidGun;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGunUpdateSignature, float, Pressure, float, MaxPressure);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTankUpdateSignature, float, FluidAmount, float, MaxFluidAmount);

UCLASS(Blueprintable)
class FLUIDGUNS_API UFG_FluidGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// Fluid gun data to update its widget.
	UPROPERTY(BlueprintAssignable)
	FOnGunUpdateSignature OnGunUpdate;
	// Tank data to update its widget.
	UPROPERTY(BlueprintAssignable)
	FOnTankUpdateSignature OnTankUpdate;

	// Array of player's tanks.
	UPROPERTY(BlueprintReadOnly, Category="FluidGunComponent|Tank")
	TArray<FTankProperties> OwnedTanks;
	
	// Array of player's fluid guns.
	UPROPERTY(BlueprintReadOnly, Category="FluidGunComponent|FluidGun")
	TArray<FFluidGunProperties> OwnedGuns;
	
	// Currently draw gun.
	UPROPERTY(BlueprintReadWrite, Category="FluidGunComponent|FluidGun")
	TObjectPtr<AFG_FluidGun> CurrentGun = nullptr;

	// Add picked up fluid gun to OwnedGuns array.
	UFUNCTION(BlueprintCallable)
	void AddFluidGun(const UFG_PDA_FluidGun* FluidGunDA);

	// Draw fluid gun and set as CurrentGun.
	UFUNCTION(BlueprintCallable)
	void DrawFluidGun(const FFluidGunProperties& FluidGun);

	// Add picked up tank to OwnedTanks array.
	UFUNCTION(BlueprintCallable)
	void AddTank(const UFG_PDA_Tank* Tank);

	// Try to find tank in array by tag and set it.
	UFUNCTION(BlueprintCallable)
	void ChangeTank(FGameplayTag TankTag);

protected:
	// Owner of this component.
	UPROPERTY(BlueprintReadWrite, Category="FluidGunComponent|PlayerCharacter")
	TObjectPtr<AFG_Player> PlayerCharacter = nullptr;

private:
	// When player pick up his first gun, actor of fluid gun will be spawn.
	void SpawnCurrentFluidGun();

	FFluidGunProperties PopulateFluidGunStructure(FFluidGunProperties& FluidGun, const UFG_PDA_FluidGun* FluidGunDA);
};
