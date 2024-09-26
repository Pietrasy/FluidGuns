// Copyright Pietras


#include "Components/FG_FluidGunComponent.h"

#include "Actors/FG_FluidGun.h"
#include "Characters/FG_Player.h"
#include "Data/FG_PDA_Tank.h"

UFG_FluidGunComponent::UFG_FluidGunComponent()
{
	// Actor will not call Tick() every frame.
	PrimaryActorTick.bCanEverTick = false;
}

const FTankProperties& UFG_FluidGunComponent::GetCurrentTank()
{
	// Check if CurrentTankIndex has been initialized.
	if (!CurrentTankIndex.IsSet())
	{
		UE_LOG(LogTemp, Fatal, TEXT("UFG_FluidGunComponent::GetCurrentTank() - Invalid CurrentTankIndex!"))
		return OwnedTanks[0];
	}
	return OwnedTanks[CurrentTankIndex.GetValue()];
}

const FFluidGunProperties& UFG_FluidGunComponent::GetCurrentFluidGun()
{
	// Check if CurrentFluidGunIndex has been initialized.
	if (!CurrentFluidGunIndex.IsSet())
	{
		UE_LOG(LogTemp, Fatal, TEXT("UFG_FluidGunComponent::GetCurrentTank() - Invalid CurrentFluidGunIndex!"))
		return OwnedGuns[0];
	}
	return OwnedGuns[CurrentFluidGunIndex.GetValue()];
}

void UFG_FluidGunComponent::AddFluidGun(const UFG_PDA_FluidGun* FluidGunDA)
{
	FFluidGunProperties FluidGun;
	// If array is empty, it indicates that this is first fluid gun, so fluid gun actor will be spawned. 
	if(OwnedGuns.IsEmpty())
	{
		SpawnCurrentFluidGun();
		PopulateFluidGunStructure(FluidGun, FluidGunDA);
		//Bind to fluid gun delegate.
		CurrentGun->OnFluidGunUpdate.AddDynamic(this, &ThisClass::OnGunUpdate);
		// Add fluid gun to array.
		OwnedGuns.Add(FluidGun);
		OnSpawnFluidGun.Broadcast();
		return;
	}
	// Check if gun is already in array.
	if (!OwnedGuns.Contains(PopulateFluidGunStructure(FluidGun, FluidGunDA)))
	{
		// Add fluid gun structure to array.
		OwnedGuns.Add(FluidGun);
	}
}

void UFG_FluidGunComponent::DrawFluidGun(FGameplayTag FluidGunTag)
{
	// Check if given fluid gun isn't the same as CurrentGun.
	if (!CurrentGun->FluidGunGameplayTag.MatchesTag(FluidGunTag))
	{
		// Cache index of array element that matches by tag.
		CurrentFluidGunIndex = OwnedGuns.IndexOfByPredicate([&FluidGunTag](const FFluidGunProperties& FluidGun)
		{
			return FluidGun.FluidGunGameplayTag.MatchesTag(FluidGunTag);
		});
		// Check if element from OwnedGuns array has been retrieved.
		if (!OwnedGuns.IsValidIndex(CurrentFluidGunIndex.GetValue()))
		{
			return;
		}
		// Overwrite fluid gun data.
		CurrentGun->SetGun(GetCurrentFluidGun());
		// Check if fluid gun has its own tank.
		if (CurrentGun->bHasOwnTank)
		{
			// Pass own tank parameters to tank structure.
			CurrentGun->ClearTankStructure();
			CurrentGun->Tank.GameplayTag = OwnedGuns[GetCurrentFluidGunIndex()].AttachedTank.GetValue();
			CurrentGun->Tank.TankData.FluidAmount = OwnedGuns[GetCurrentFluidGunIndex()].OwnTankFluidAmount;
			CurrentGun->Tank.TankData.MaxFluidAmount = OwnedGuns[GetCurrentFluidGunIndex()].OwnTankMaxFluidAmount;
			CurrentGun->SetTank(CurrentGun->Tank);
			// Reset CurrentTankIndex to become uninitialised and call delegate.
			CurrentTankIndex.Reset();
			OnTankUpdate.Broadcast(OwnedGuns[GetCurrentFluidGunIndex()].OwnTankMaxFluidAmount,OwnedGuns[GetCurrentFluidGunIndex()].OwnTankFluidAmount, CurrentGun->Tank.GameplayTag);
		}
		else
		{
			CurrentGun->ClearTankStructure();
		}
		// Check if fluid gun has been assigned tank.
		if (GetCurrentFluidGun().AttachedTank.IsSet())
		{
 			ChangeTank(GetCurrentFluidGun().AttachedTank.GetValue());
		}
		// Update widget with values of fluid gun and tank parameters.
		OnDrawFluidGun.Broadcast(GetCurrentFluidGun().FluidGunData.MaxPressure);
		CurrentGun->UpdateGun();
	}
}

void UFG_FluidGunComponent::AddTank(const UFG_PDA_Tank* Tank)
{
	// Check if tank is already in array.
	if (!OwnedTanks.Contains(PopulateTankStructure(Tank)))
	{
		// Add tank structure to array.
		OwnedTanks.Add(PopulateTankStructure(Tank));
	}
}

void UFG_FluidGunComponent::ChangeTank(const FGameplayTag TankTag)
{
	// If CurrentGun isn't valid, do not allow change tank.
	if (!IsValid(CurrentGun))
	{
		return;
	}
	// Check whether fluid gun has own tank.
	if (CurrentGun->bHasOwnTank)
	{
		// Reset CurrentTankIndex to become uninitialised
		CurrentTankIndex.Reset();
		return;
	}
	// Check array for element with specified tag and, if so, returns its index.
	CurrentTankIndex = OwnedTanks.IndexOfByPredicate([&TankTag](const FTankProperties& Tank)
	{
		// Lambda checks tag match for each element in array.
		return Tank.GameplayTag.MatchesTag(TankTag);
	});
	// Set up tank for fluid gun and assign tag of new tank to current fluid gun.
	CurrentGun->SetTank(GetCurrentTank());
	OwnedGuns[CurrentFluidGunIndex.GetValue()].AttachedTank = TankTag;
	// Update widget with values of tank parameters.
	OnTankUpdate.Broadcast(OwnedTanks[CurrentTankIndex.GetValue()].TankData.MaxFluidAmount, OwnedTanks[CurrentTankIndex.GetValue()].TankData.FluidAmount, CurrentGun->Tank.GameplayTag);
}

void UFG_FluidGunComponent::OnGunUpdate(float PressureLevel, float FluidAmount)
{
	// Override pressure level of fluid gun in OwnedGuns with value from OnFluidGunUpdate delegate.
	OwnedGuns[CurrentFluidGunIndex.GetValue()].FluidGunData.Pressure = PressureLevel;
	const float Pressure = OwnedGuns[CurrentFluidGunIndex.GetValue()].FluidGunData.Pressure;
	float Fluid = 0.f;
	// Check whether fluid gun has own tank.
	if (CurrentGun->bHasOwnTank)
	{
		OwnedGuns[CurrentFluidGunIndex.GetValue()].OwnTankFluidAmount = FluidAmount;
		// Override fluid amount of own tank with value from OnFluidGunUpdate delegate.
		CurrentGun->Tank.TankData.FluidAmount = FluidAmount;
		Fluid = CurrentGun->Tank.TankData.FluidAmount;
		// Update widget with values of fluid gun and tank parameters.
		OnGunParamsUpdate.Broadcast(Pressure, Fluid);
		return;
	}
	// Check if CurrentTankIndex has been initialized.
	if (CurrentTankIndex.IsSet())
	{
		// Override fluid amount of current gun tank with value from OnFluidGunUpdate delegate.
		Fluid = OwnedTanks[CurrentTankIndex.GetValue()].TankData.FluidAmount = FluidAmount;
	}
	// Update widget with values of fluid gun and tank parameters.
	OnGunParamsUpdate.Broadcast(Pressure, Fluid);
}

int32 UFG_FluidGunComponent::GetCurrentFluidGunIndex()
{
	return CurrentFluidGunIndex.GetValue();
}

void UFG_FluidGunComponent::SpawnCurrentFluidGun()
{
	// Spawn fluid gun actor.
	if (!IsValid(FluidGunClass))
	{
		UE_LOG(LogTemp, Error, TEXT("UFG_FluidGunComponent::SpawnCurrentFluidGun - Invalid Fluid Gun Class"))
		return;
	}
	CurrentGun = GetWorld()->SpawnActor<AFG_FluidGun>(FluidGunClass);
	CastChecked<AFG_FluidGun>(CurrentGun);
}

FFluidGunProperties UFG_FluidGunComponent::PopulateFluidGunStructure(FFluidGunProperties& FluidGun, const UFG_PDA_FluidGun* FluidGunDA)
{
	FluidGun.FluidGunData = FluidGunDA->FluidGunData;
	FluidGun.StaticMesh = FluidGunDA->ItemStaticMesh;
	FluidGun.FluidGunGameplayTag = FluidGunDA->ItemGameplayTag;
	FluidGun.FluidGunName = FluidGunDA->ItemName;
	FluidGun.Addons = FluidGunDA->Addons;
	FluidGun.bHasOwnTank = FluidGunDA->bHasOwnTank;
	FluidGun.bConstPressure = FluidGunDA->bIsPressureConst;
	// If fluid gun has its own tank, set it up.
	if(FluidGunDA->bHasOwnTank)
	{
		FluidGun.AttachedTank = FluidGunDA->OwnTank->ItemGameplayTag;
		FluidGun.OwnTankFluidAmount = FluidGunDA->OwnTank->TankParameters.FluidAmount;
		FluidGun.OwnTankMaxFluidAmount = FluidGunDA->OwnTank->TankParameters.MaxFluidAmount;
		// Reset CurrentTankIndex to become uninitialised and set fluid gun tank.
		CurrentTankIndex.Reset();
		CurrentGun->SetTank(PopulateTankStructure(FluidGunDA->OwnTank), true);
	}
	return FluidGun;
}

FTankProperties UFG_FluidGunComponent::PopulateTankStructure(const UFG_PDA_Tank* NewTank)
{
	FTankProperties FluidTank;
	FluidTank.TankData = NewTank->TankParameters;
	FluidTank.StaticMesh = NewTank->ItemStaticMesh;
	FluidTank.GameplayTag = NewTank->ItemGameplayTag;
	FluidTank.Name = NewTank->ItemName;
	return FluidTank;
}