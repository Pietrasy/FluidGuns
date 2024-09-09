// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/FG_FFluidGunStructure.h"
#include "FG_FluidGun.generated.h"

UCLASS()
class FLUIDGUNS_API AFG_FluidGun : public AActor
{
	GENERATED_BODY()

public:
	AFG_FluidGun();
	
	UPROPERTY(VisibleInstanceOnly, Category="FluidGun")
	FG_FFluidGunStructure FluidGunProperties;
	
	UFUNCTION()
	void UpdateGun(const FG_FFluidGunStructure& FluidGun);

private:
	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	TObjectPtr<UStaticMeshComponent> FluidGunStaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	FName FluidGunName;

	UPROPERTY(VisibleAnywhere, Category="FluidGun")
	FGameplayTag FluidGunGameplayTag = FGameplayTag::EmptyTag;
};
