// Copyright Pietras


#include "Actors/FG_FluidGun.h"

#include "Components/FG_Addon.h"

AFG_FluidGun::AFG_FluidGun()
{
	// Create static mesh component, set it as root and set its collision profile.
	FluidGunStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("FluidGunStaticMesh");
	SetRootComponent(FluidGunStaticMesh);
	FluidGunStaticMesh->SetCollisionProfileName("NoCollision", false);
}

void AFG_FluidGun::UpdateGun(const FFluidGunProperties& FluidGun)
{
	FluidGunParameters = FluidGun.FluidGunData;
	FluidGunName = FluidGun.FluidGunName;
	FluidGunGameplayTag = FluidGun.FluidGunGameplayTag;
	FluidGunStaticMesh->SetStaticMesh(FluidGun.StaticMesh);

	RemoveAddons();
	
	for (TSubclassOf<UFG_Addon> AddonClass : FluidGun.Addons)
	{
		AddAddon(AddonClass);
	}
}

UFG_Addon* AFG_FluidGun::GetAddon(const FGameplayTag AddonTag)
{
	for (UFG_Addon* Addon : Addons)
	{
		if (Addon->AddonTag.MatchesTag(AddonTag))
		{
			return Addon;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Addon not found"))
	return nullptr;
}

void AFG_FluidGun::AddAddon(const TSubclassOf<UFG_Addon>& AddonClass)
{
	// Create addon as component.
	UFG_Addon* AddonFromArray = NewObject<UFG_Addon>(this, AddonClass, TEXT("AddonStaticMesh"));
		
	AddonFromArray->RegisterComponent();
	AddInstanceComponent(AddonFromArray);
	
	AddonFromArray->CreationMethod = EComponentCreationMethod::Instance;

	// Attach addon to fluid gun.
	const FAttachmentTransformRules TransStruct(EAttachmentRule::SnapToTarget, true);
	AddonFromArray->AttachToComponent(FluidGunStaticMesh, TransStruct);

	// Add addon to array.
	Addons.Add(AddonFromArray);
}

void AFG_FluidGun::RemoveAddons()
{
	// Add all components of UFG_Addon class to temp array.
	TArray<UActorComponent*> Components;
	GetComponents(UFG_Addon::StaticClass(), Components);

	// Destroy all components.
	for (UActorComponent* Addon : Components)
	{
		Addon->DestroyComponent();
	}

	// Clear Addons array.
	Addons.Empty();
}
