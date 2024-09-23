// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/FG_FFluidGunParameters.h"
#include "Structures/FG_FFluidGunProperties.h"
#include "Structures/FG_FTankProperties.h"
#include "FG_FluidGun.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSetGun);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFluidGunUpdateSignature, float, PressureLevel, float, FluidAmout);

class UFG_PDA_Tank;
class UFG_Addon;

UCLASS()
class FLUIDGUNS_API AFG_FluidGun : public AActor
{
	GENERATED_BODY()

public:
	AFG_FluidGun();

	// Call when setting up new gun.
	UPROPERTY(BlueprintAssignable, Category="FluidGun|Delegate")
	FOnSetGun OnSetGun;
	
	// Delegate to pass values of pressure level and fluid amount.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="FluidGun|Delegate")
	FOnFluidGunUpdateSignature OnFluidGunUpdate;
	
	// Pressure, range, fire rate, etc.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FluidGun")
	FFluidGunParameters FluidGunParameters;
	
	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	FGameplayTag FluidGunGameplayTag = FGameplayTag::EmptyTag;
	
	// Current tank attached to fluid gun.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FluidGun|Tank")
	FTankProperties Tank;
	
	// If fluid gun has its own tank, it can't be changed.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FluidGun|Tank")
	bool bHasOwnTank = false;
	
	// Indicates whether fluid gun has constant pressure level.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FluidGun")
	bool bIsPressureConst = false;
	
	// Set fluid gun members.
	UFUNCTION(BlueprintCallable, Category="FluidGun")
	void SetGun(const FFluidGunProperties& FluidGun);

	// Set structure of new tank and set its static mesh.
	UFUNCTION(BlueprintCallable, Category="FluidGun|Tank")
	void SetTank(const FTankProperties& NewTank, const bool bOwnTank = false);

	// Pass pressure level and fluid amount in delegate. 
	UFUNCTION(BlueprintCallable, Category="FluidGun")
	void UpdateGun() const;

	// Set fluid amount to maximum value of tank.
	UFUNCTION(BlueprintCallable, Category="FluidGun|Tank")
	void RefillTank();

	// Calculation parameters needed for fire.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="FluidGun|Shooting")
	void Fire(bool& bCanShot);

	// Set tank structure as empty.
	void ClearTankStructure();

protected:
	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	FName FluidGunName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FluidGun")
	TObjectPtr<UStaticMeshComponent> FluidGunStaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FluidGun|Tank")
	TObjectPtr<UStaticMeshComponent> TankStaticMesh = nullptr;

	// Addons that have been added to fluid gun.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FluidGun|Addon")
	TArray<TObjectPtr<UFG_Addon>> Addons;

	// Indicates whether gun can fire.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="FluidGun|Shooting")
	bool bCanFire = true;

	// Timer handle to determine cooldown between shots.
	UPROPERTY(BlueprintReadOnly, Category="FluidGun|Shooting")
	FTimerHandle FireDelayTimerHandle;

	// Get addon from Addons array by gameplay tag.
	UFUNCTION(BlueprintCallable, Category="FluidGun|Addon", meta=(ReturnDisplayName="Addon"))
	UFG_Addon* GetAddon(const FGameplayTag AddonTag);
	
private:
	// Indicates whether gun has tank.
	bool bHasTank = false;

	// Add addon to Addons array.
	void AddAddon(const TSubclassOf<UFG_Addon>& AddonClass);

	/// Remove all addons from fluid gun.
	void RemoveAddons();

	// Assign values of new fluid gun.
	void PopulateFluidGunMembers(const FFluidGunProperties& FluidGun);

	// When FireDelayTimerHandle ends, set bCanFire to true.
	void SetFire();
};
