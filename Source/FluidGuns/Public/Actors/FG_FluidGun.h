// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/FG_FFluidGunParameters.h"
#include "Structures/FG_FFluidGunProperties.h"
#include "FG_FluidGun.generated.h"

UCLASS()
class FLUIDGUNS_API AFG_FluidGun : public AActor
{
	GENERATED_BODY()

public:
	AFG_FluidGun();
	
	// Set gun's properties.
	UFUNCTION()
	void UpdateGun(const FFluidGunProperties& FluidGun);

	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	FGameplayTag FluidGunGameplayTag = FGameplayTag::EmptyTag;

private:
	UPROPERTY(VisibleInstanceOnly, Category="FluidGun")
	FFluidGunParameters FluidGunProperties;
	
	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	TObjectPtr<UStaticMeshComponent> FluidGunStaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	FName FluidGunName;


};
