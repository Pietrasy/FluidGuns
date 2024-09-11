// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/FG_FFluidGunParameters.h"
#include "Structures/FG_FFluidGunProperties.h"
#include "FG_FluidGun.generated.h"

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

	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	FName FluidGunName;

	// Add addon to Addons array.
	void AddAddon(const TSubclassOf<UFG_Addon>& AddonClass);

	// Remove all addons in Array.
	void RemoveAddons();
};
