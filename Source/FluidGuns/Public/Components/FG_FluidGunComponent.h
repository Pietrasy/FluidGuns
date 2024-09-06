// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/FG_PDA_FluidGun.h"
#include "FG_FluidGunComponent.generated.h"

USTRUCT(BlueprintType)
struct FFluidGun
{
	GENERATED_BODY()

	// Base structure for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	FFluidGunData FluidGunData;

	// Static mesh for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;

	// Gameplay tag for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag FluidGunGameplayTag = FGameplayTag::EmptyTag;

	// Name for fluid gun.
	UPROPERTY(BlueprintReadWrite)
	FName FluidGunName;
};

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

private:
	// Array of player's fluid guns.
	UPROPERTY(BlueprintReadOnly, Category="Component|FluidGun", meta=(AllowPrivateAccess))
	TArray<FFluidGun> OwnedGuns;
};
