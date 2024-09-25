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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDrawFluidGunSignature, float, MaxPressure);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTankUpdateSignature, float, MaxFluidAmount, float, FluidAmount, FGameplayTag, FluidType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateSignature, float, Pressure, float, FluidAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnFluidGun);

UCLASS(Blueprintable)
class FLUIDGUNS_API UFG_FluidGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// Call when fluid gun is spawned.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="FluidGunComponent|Delegate")
	FOnSpawnFluidGun OnSpawnFluidGun;
	
	// Delegate to pass values of pressure level and fluid amount.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="FluidGunComponent|Delegate")
	FOnUpdateSignature OnGunParamsUpdate;

	// Delegate to pass information about maximum pressure level.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="FluidGunComponent|Delegate")
	FOnDrawFluidGunSignature OnDrawFluidGun;
	
	// Delegate to pass information about fluid amount of tank and it maximum fluid amount.
	UPROPERTY(BlueprintAssignable, Category="FluidGunComponent|Delegate")
	FOnTankUpdateSignature OnTankUpdate;
	
	// Currently draw fluid gun.
	UPROPERTY(BlueprintReadOnly, Category="FluidGunComponent|FluidGun")
	TObjectPtr<AFG_FluidGun> CurrentGun = nullptr;
	
	// Array of player's fluid guns.
	UPROPERTY(BlueprintReadOnly, Category="FluidGunComponent|FluidGun")
	TArray<FFluidGunProperties> OwnedGuns;

	// Array of player's tanks.
	UPROPERTY(BlueprintReadOnly, Category="FluidGunComponent|Tank")
	TArray<FTankProperties> OwnedTanks;
	
	// Retrieving tank from array based on CurrentTankIndex.
	UFUNCTION(BlueprintPure, Category="FluidGunComponent|Tank")
	const FTankProperties& GetCurrentTank();

	// Retrieving fluid gun from array based on CurrentFluidGunIndex.
	UFUNCTION(BlueprintPure, Category="FluidGunComponent|FluidGun")
	const FFluidGunProperties& GetCurrentFluidGun();
	
	// Add picked-up fluid gun to OwnedGuns array.
	UFUNCTION(BlueprintCallable, Category="FluidGunComponent|FluidGun")
	void AddFluidGun(const UFG_PDA_FluidGun* FluidGunDA);

	// Draw fluid gun and set as CurrentGun.
	UFUNCTION(BlueprintCallable, Category="FluidGunComponent|FluidGun")
	void DrawFluidGun(FGameplayTag FluidGunTag);

	// Add picked up tank to OwnedTanks array.
	UFUNCTION(BlueprintCallable, Category="FluidGunComponent|Tank")
	void AddTank(const UFG_PDA_Tank* Tank);

	// Try to find tank in array by tag and set it.
	UFUNCTION(BlueprintCallable, Category="FluidGunComponent|Tank")
	void ChangeTank(FGameplayTag TankTag);

protected:
	// Owner of this component.
	UPROPERTY(BlueprintReadWrite, Category="FluidGunComponent|PlayerCharacter")
	TObjectPtr<AFG_Player> PlayerCharacter = nullptr;

	// Blueprint class of Fluid Gun to be created.
	UPROPERTY(EditDefaultsOnly, Category="FluidGunComponent|FluidGun")
	TSubclassOf<AActor> FluidGunClass = nullptr;

	// Callback function to OnFluidGunUpdate from FG_FluidGun. Call OnGunParamsUpdate delegate.
	UFUNCTION()
	void OnGunUpdate(float PressureLevel, float FluidAmount);

	// Return array index of current fluid gun.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FluidGun")
	int32 GetCurrentFluidGunIndex();

private:
	// Index of equivalent current fluid gun in OwnedGuns array. Needed for update structures in array.
	TOptional<int32> CurrentFluidGunIndex;
	
	// Index of equivalent current tank in OwnedTanks array. Needed for update structures in array.
	TOptional<int32> CurrentTankIndex;
	
	// When player picks up their first gun, fluid gun actor will be spawned.
	void SpawnCurrentFluidGun();

	// Copy data from data asset of fluid gun and cache it in component's structure.
	FFluidGunProperties PopulateFluidGunStructure(FFluidGunProperties& FluidGun, const UFG_PDA_FluidGun* FluidGunDA);

	// Makes tank structure from tank data asset and return it.
	FTankProperties PopulateTankStructure(const UFG_PDA_Tank* NewTank);
};