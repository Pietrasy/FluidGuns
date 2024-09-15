// Copyright Pietras


#include "Components/FG_FluidGunComponent.h"

#include "Actors/FG_FluidGun.h"
#include "Characters/FG_Player.h"
#include "Data/FG_PDA_Tank.h"

void UFG_FluidGunComponent::BeginPlay()
{
	// Get owner of this component and set as PlayerCharacter.
	PlayerCharacter = CastChecked<AFG_Player>(GetOwner());

	Super::BeginPlay();
}

void UFG_FluidGunComponent::AddFluidGun(const UFG_PDA_FluidGun* FluidGunDA)
{
	FFluidGunProperties FluidGun;
	
	if(OwnedGuns.IsEmpty())
	{
		SpawnCurrentFluidGun();
		PopulateFluidGunStructure(FluidGun, FluidGunDA);
		OwnedGuns.Add(FluidGun);
		return;
	}
	
	// Check if gun is already in array.
	if (!OwnedGuns.Contains(PopulateFluidGunStructure(FluidGun, FluidGunDA)))
	{
		// Add fluid gun structure to array.
		OwnedGuns.Add(FluidGun);
	}
}

void UFG_FluidGunComponent::DrawFluidGun(const FFluidGunProperties& FluidGun)
{
	// Check if given gun isn't the same as CurrentGun.
	if (!CurrentGun->FluidGunGameplayTag.MatchesTag(FluidGun.FluidGunGameplayTag))
	{
		// Overwrite fluid gun's data. 
		CurrentGun->UpdateGun(FluidGun);
		OnGunUpdate.Broadcast(FluidGun.FluidGunData.Pressure, FluidGun.FluidGunData.MaxPressure);
	}
}

void UFG_FluidGunComponent::AddTank(const UFG_PDA_Tank* Tank)
{
	for (FTankProperties& FluidTank : OwnedTanks)
	{
		// Check if tank is already in array.
		if (!FluidTank.GameplayTag.MatchesTag(Tank->ItemGameplayTag))
		{
			return;
		}
	}

	// Add tank structure to array.
	OwnedTanks.Add(CurrentGun->PopulateTankStructure(Tank));
}

void UFG_FluidGunComponent::ChangeTank(const FGameplayTag TankTag)
{
	if (!IsValid(CurrentGun) || CurrentGun->Tank.GameplayTag.MatchesTag(TankTag) || CurrentGun->bHasOwnTank)
	{
		return;
	}

	for (FTankProperties& Tank : OwnedTanks)
	{
		if (Tank.GameplayTag.MatchesTag(TankTag))
		{
			// If in arrays is that tank, set it and call delegate.
			CurrentGun->SetTank(Tank);
			OnTankUpdate.Broadcast(Tank.TankData.FluidAmount, Tank.TankData.MaxFluidAmount);
		}
	}
}

void UFG_FluidGunComponent::SpawnCurrentFluidGun()
{
	// Set spawn actor's structure.
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = PlayerCharacter;
	SpawnParams.Owner = PlayerCharacter;

	// Spawn fluid gun.
	CurrentGun = GetWorld()->SpawnActor<AFG_FluidGun>(SpawnParams);

	// Attach to player character.
	CurrentGun->AttachToActor(PlayerCharacter, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

FFluidGunProperties UFG_FluidGunComponent::PopulateFluidGunStructure(FFluidGunProperties& FluidGun, const UFG_PDA_FluidGun* FluidGunDA)
{
	// Copy data from fluid gun's data asset and cache its in component's structure.
	FluidGun.FluidGunData = FluidGunDA->FluidGunData;
	FluidGun.StaticMesh = FluidGunDA->ItemStaticMesh;
	FluidGun.FluidGunGameplayTag = FluidGunDA->ItemGameplayTag;
	FluidGun.FluidGunName = FluidGunDA->ItemName;
	FluidGun.bHasOwnTank = FluidGunDA->bHasOwnTank;
			
	if(FluidGunDA->bHasOwnTank)
	{
		CurrentGun->SetTank(CurrentGun->PopulateTankStructure(FluidGunDA->OwnTank), true);
	}

	return FluidGun;
}