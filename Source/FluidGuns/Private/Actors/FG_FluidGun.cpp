// Copyright Pietras


#include "Actors/FG_FluidGun.h"

#include "Data/FG_PDA_Tank.h"

AFG_FluidGun::AFG_FluidGun()
{
	// Create fluid gun static mesh component, set it as root component and set its collision profile.
	FluidGunStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("FluidGunStaticMesh");
	SetRootComponent(FluidGunStaticMesh);
	FluidGunStaticMesh->SetCollisionProfileName("NoCollision", false);
	// Create tank static mesh component, attach it to fluid gun and set its collision profile.
	TankStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("TankStaticMesh");
	TankStaticMesh->SetupAttachment(FluidGunStaticMesh);
	TankStaticMesh->SetCollisionProfileName("NoCollision", false);
}

void AFG_FluidGun::SetGun(const FFluidGunProperties& FluidGun)
{
	// Call delegate at the start of setting up new fluid gun.
	OnSetGun.Broadcast();
	// Clear fire delay timer handle and set bCanFire to true.
	GetWorld()->GetTimerManager().ClearTimer(FireDelayTimerHandle);
	SetFire();
	RemoveAddons();
	PopulateFluidGunMembers(FluidGun);
	// Add new addons to fluid gun.
	for (TSubclassOf<UFG_Addon> AddonClass : FluidGun.Addons)
	{
		AddAddon(AddonClass);
	}
}

void AFG_FluidGun::SetTank(const FTankProperties& NewTank, const bool bOwnTank)
{
	// Assign new tank structure and set flag that says fluid gun has tank.
	Tank = NewTank;
	bHasTank = true;
	// If bOwnTank is true, set static mesh to nullptr, otherwise set static mesh of new tank.
	bOwnTank ? TankStaticMesh->SetStaticMesh(nullptr) : TankStaticMesh->SetStaticMesh(NewTank.StaticMesh);
}

void AFG_FluidGun::UpdateGun() const
{
	OnFluidGunUpdate.Broadcast(FluidGunParameters.Pressure, Tank.TankData.FluidAmount);
}

void AFG_FluidGun::RefillTank()
{
	Tank.TankData.FluidAmount = Tank.TankData.MaxFluidAmount;
	UpdateGun();
}

void AFG_FluidGun::Fire_Implementation(bool& bCanShot)
{
	// If ShotsNumber is less than or equal to zero, tank is not attached, pressure or fluid amount is less than or equal to zero, or bCanFire is false, then do not allow firing.
	if (FluidGunParameters.ShotsNumber <= 0 || !bHasTank || FluidGunParameters.Pressure <= 0.f || Tank.TankData.FluidAmount <= 0.f || !bCanFire)
	{
		if (bCanFire) UE_LOG(LogTemp, Log, TEXT("AFG_FluidGun::Fire_Implementation() - It is not possible to fire. "));
		return;
	}
	// Set output parameter and set flag that is responsible for shot to false.
	bCanShot = bCanFire;
	bCanFire = false;
	// Set timer to time next shot based on FireRate.
	const UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(FireDelayTimerHandle, this, &AFG_FluidGun::SetFire, FluidGunParameters.FireRate, false);
	/* RANGE CALCULATION */
	// Range depends on current pressure level and BaseRange.
	FluidGunParameters.Range = FluidGunParameters.Pressure * FluidGunParameters.BaseRange;
	/* PRESSURE CALCULATION */
	// Check if fluid gun has constant pressure.
	if (!bIsPressureConst)
	{
		// Calculate pressure cost from the formula.
		const float PressureCostFormula = FluidGunParameters.MaxPressure / (FluidGunParameters.ShotsNumber * 0.25f);
		// If PressureCost is less than one, set value to one.
		float PressureCost = PressureCostFormula < 1 ? PressureCost = 1 : PressureCostFormula;
		// Subtract PressureCost from current pressure level and clamp subtraction result.
		const float ClampValue = FluidGunParameters.Pressure - PressureCost;
		FluidGunParameters.Pressure = FMath::Clamp(ClampValue, 0, FluidGunParameters.MaxPressure);
	}
	/* FLUID CALCULATION */
	// Calculate FluidCost from formula.
	const float FluidCost = Tank.TankData.MaxFluidAmount / FluidGunParameters.ShotsNumber;
	// Subtract fluid cost from current fluid amount and clamp subtraction result.
	const float ClampValue = Tank.TankData.FluidAmount - FluidCost;
	Tank.TankData.FluidAmount = FMath::Clamp(ClampValue, 0, Tank.TankData.MaxFluidAmount);
	UpdateGun();
}

UFG_Addon* AFG_FluidGun::GetAddon(const FGameplayTag AddonTag)
{
	// Check if addon is in array.
	for (UFG_Addon* Addon : Addons)
	{
		if (Addon->AddonTag.MatchesTag(AddonTag))
		{
			return Addon;
		}
	}
	// If there is no addon, return nullptr.
	return nullptr;
}

void AFG_FluidGun::AddAddon(const TSubclassOf<UFG_Addon>& AddonClass)
{
	// Create addon as component.
	UFG_Addon* AddonFromArray = NewObject<UFG_Addon>(this, AddonClass, TEXT("AddonStaticMesh"));
	AddInstanceComponent(AddonFromArray);
	AddonFromArray->CreationMethod = EComponentCreationMethod::Instance;
	AddonFromArray->RegisterComponent();
	// Attach addon to fluid gun.
	const FAttachmentTransformRules TransStruct(EAttachmentRule::SnapToTarget, true);
	AddonFromArray->AttachToComponent(FluidGunStaticMesh, TransStruct);
	// Add addon to array.
	Addons.Add(AddonFromArray);
}

void AFG_FluidGun::RemoveAddons()
{
	// Add all components of UFG_Addon class to temporary array.
	TArray<UActorComponent*> Components;
	GetComponents(UFG_Addon::StaticClass(), Components);
	// Destroy all components.
	for (UActorComponent* Addon : Components)
	{
		Addon->DestroyComponent();
	}
	// Clear array of addons.
	Addons.Empty();
}

void AFG_FluidGun::PopulateFluidGunMembers(const FFluidGunProperties& FluidGun)
{
	FluidGunParameters = FluidGun.FluidGunData;
	FluidGunName = FluidGun.FluidGunName;
	FluidGunGameplayTag = FluidGun.FluidGunGameplayTag;
	FluidGunStaticMesh->SetStaticMesh(FluidGun.StaticMesh);
	bHasOwnTank = FluidGun.bHasOwnTank;
	bIsPressureConst = FluidGun.bConstPressure;
}

void AFG_FluidGun::SetFire()
{
	bCanFire = true;
}

void AFG_FluidGun::ClearTankStructure()
{
	Tank.TankData.FluidAmount = 0.f;
	Tank.TankData.MaxFluidAmount = 0.f;
	Tank.StaticMesh = nullptr;
	Tank.GameplayTag = FGameplayTag::EmptyTag;
	Tank.Name = "";
}
