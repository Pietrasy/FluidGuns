// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/FG_FFluidGunParameters.h"
#include "Structures/FG_FFluidGunProperties.h"
#include "Structures/FG_FTankProperties.h"
#include "FG_FluidGun.generated.h"

class UFG_PDA_Tank;
class UFG_Addon;

UCLASS()
class FLUIDGUNS_API AFG_FluidGun : public AActor
{
	GENERATED_BODY()

public:
	AFG_FluidGun();
	
	// Set fluid gun properties.
	UFUNCTION()
	void UpdateGun(const FFluidGunProperties& FluidGun);

	// Fluid gun gameplay tag.
	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	FGameplayTag FluidGunGameplayTag = FGameplayTag::EmptyTag;

	// Current tank of fluid gun.
	UPROPERTY(VisibleAnywhere, Category="FluidGun|Tank")
	FTankProperties Tank;

	// If fluid gun has its own tank, it can't be changed.
	UPROPERTY(VisibleAnywhere, Category="FluidGun|Tank")
	bool bHasOwnTank = false;

	// Set new tank and its static mesh. When bOwnTank is false, static mesh will be clear.
	UFUNCTION(BlueprintCallable)
	void SetTank(const FTankProperties NewTank, const bool bOwnTank = false);

	// Make and return structure from tank data asset.
	FTankProperties PopulateTankStructure(const UFG_PDA_Tank* NewTank);

protected:
	// Pressure, range, fire rate, etc.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  Category="FluidGun")
	FFluidGunParameters FluidGunParameters;

	// Addons that have been added to fluid gun.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  Category="FluidGun|Addon")
	TArray<TObjectPtr<UFG_Addon>> Addons;

	// Get addon from Addons array by gameplay tag.
	UFUNCTION(BlueprintCallable, Category="FluidGun|Addon", meta=(ReturnDisplayName="Addon"))
	UFG_Addon* GetAddon(const FGameplayTag AddonTag);
	
private:
	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	TObjectPtr<UStaticMeshComponent> FluidGunStaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category="FluidGun|Tank")
	TObjectPtr<UStaticMeshComponent> TankStaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	FName FluidGunName;

	// Add addon to Addons array.
	void AddAddon(const TSubclassOf<UFG_Addon>& AddonClass);

	// Remove all addons in Array.
	void RemoveAddons();
};
