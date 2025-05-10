# Fluid Guns
This project is based on a system for managing fluid guns, allowing for the addition of new guns, gun addons, and fluid tanks. Guns and tanks can be spawned by a spawner, picked up by the player, and refilled at fluid sources.
<br />



### Table of Content:
[General Overview](#general-overview)<br />
[Controls](#controls)<br />
[Creating a Fluid Gun Data Asset](#creating-a-fluid-gun-data-asset)<br />
[Creating a Tank Data Asset](#creating-a-tank-data-asset)<br />
[Setting Up Spawner](#setting-up-spawner)<br />
[Creating an Addon](#creating-an-addon)<br />
[Creating a Fluid Source](#creating-a-fluid-source)<br />
[Set Up a Slot for the New Fluid Gun](#set-up-a-slot-for-the-new-fluid-gun)<br />
[Code Snipppets](#code-snippets)<br />

## General Overview
https://github.com/user-attachments/assets/197d2a53-8a1c-43e3-83af-7afb6562e335

The player can pick up a fluid gun, but to use it, they must also pick up a tank. Once collected, they must select it from the tank selection menu (unless the fluid gun has its own tank, in which case it can be used immediately).<br />
At the top of the screen, there is a bar that indicates the amount and type of fluid in the tank. If the fluid in the tank runs out, it can be replenished at the appropriate fluid source.<br />
Each fluid gun has a specific pressure level, which is also displayed on the bar. After each shot (unless the pressure level is set to constant), this level decreases, affecting the fluid gun's range. Using a pump addon, the pressure in the gun can be increased.
<br />

## Controls
- **Left Mouse Button** - Fire<br />
- **Scroll Wheel** - Change to the next or previous fluid gun<br />
- **R** - Tank selection menu<br />
- **E** - Use<br />
- **Space** - Pump<br />
- **1** - Change to a pistol<br />
- **2** - Change to a rifle<br />

## Creating a Fluid Gun Data Asset
Create a data asset that inherits from **FG_PDA_FluidGun**, and set the parameters and properties of the gun.<br />
![Creating Fluid Gun DA](https://github.com/user-attachments/assets/5e0ef761-0efa-46d8-bce2-4aa3daf65730)
![2  Setup Fluid Gun DA 2](https://github.com/user-attachments/assets/a2d98cfb-e4cb-4703-86a3-cc33693c40ad)
<br />If an [addon is created](#creating-an-addon), it can be added to the gun.<br />
![4  Set Addon](https://github.com/user-attachments/assets/e9b831d3-6622-4eb4-b3cd-fd7584866631)
<br />The action determines which function is performed when the item is picked up. We now creating a fluid gun so select "**Add Fluid Gun Action**".<br />
![3  Set Action](https://github.com/user-attachments/assets/433a7d5f-5a9d-4bf6-8a26-23e0c89f3c7c)


[Back to top](#table-of-content)

## Creating a Tank Data Asset
Create a data asset that inherits from **FG_PDA_Tank** and set the parameters and properties of the tank.<br />
![5  Creating Tank DA](https://github.com/user-attachments/assets/525d818b-9075-4e7b-9b3f-0c179fd81d5e)
![6  Setup Tank DA 2](https://github.com/user-attachments/assets/5d3de5a7-9f50-4c63-89cf-be161bdc0965)

[Back to top](#table-of-content)

## Setting Up Spawner
Place the **BP_Spawner** in the level and set the item to spawn.<br />
![7  Set DA on Spawner](https://github.com/user-attachments/assets/a1e80835-6414-4a1d-8d37-41421dc2666c)


[Back to top](#table-of-content)

## Creating an Addon
Create a blueprint class for **BP_Addons** and configure its properties.<br />
![8  Creating child addon](https://github.com/user-attachments/assets/83dd2227-3993-49d6-be71-30d115007ca6)
![9  Setup addon](https://github.com/user-attachments/assets/c27b2174-c81c-4673-b102-c029b8fd27b7)

[Back to top](#table-of-content)

## Creating a Fluid Source
Place the **BP_FluidSource** in the level and set a gameplay tag for the fluid type.<br />
![10  Set fluid type to Fluid Source](https://github.com/user-attachments/assets/ba337cf2-9a4f-40b4-9aaf-25442aad06e9)
<br />Add a new row to **DT_FluidColors** and choose a color for the gameplay tag.<br />
![11  Add Fluid to DT](https://github.com/user-attachments/assets/403c649c-1b91-44da-bd34-24fa2530724e)

[Back to top](#table-of-content)

## Set Up a Slot for the New Fluid Gun
Add input to **IMC_FluidGunComponent.**<br />
![12  Adding input to IMC](https://github.com/user-attachments/assets/8c5d452c-9633-4210-b1cd-ce88b0bd90a1)
<br />Handle input for the new slot in **BP_FluidGunComponent**.<br />
![13  Set up input](https://github.com/user-attachments/assets/bb2d272f-c172-4c39-a112-9b1698185f96)

[Back to top](#table-of-content)

## Code Snippets
Checks whether the gun can fire based on tank condition, pressure level and fluid availability.<br />
Sets a timer that disables firing for a specified time in FireRate.<br />
Calculates dynamic range based on current pressure.<br /> 
Handles fluid consumption and pressure per shot.<br /> 
Triggers UpdateGun() to update weapon parameters and synchronize status in the user interface.<br />
```cpp
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
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("AFG_FluidGun::Fire_Implementation - Invalid World"))
	}
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
```
-----------
The method handles dynamic switching between fluid tanks, which we select from the menu.<br /> 
We have given the function a gameplay tag of the liquid and it searches the OwnedTanks array to find a matching tank in the inventory.<br />
Assigns a new tank to the current fluid gun.<br /> 
Uses a delegate to update the widget showing the amount of fluid in the tank.<br />

```cpp
void UFG_FluidGunComponent::ChangeTank(const FGameplayTag TankTag)
{
	// If CurrentGun isn't valid, do not allow change tank.
	if (!IsValid(CurrentGun))
	{
		UE_LOG(LogTemp, Error, TEXT("UFG_FluidGunComponent::ChangeTank - CurrentGun isn't valid"))
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
	if (!CurrentFluidGunIndex.IsSet())
	{
		UE_LOG(LogTemp, Error, TEXT("UFG_FluidGunComponent::ChangeTank - CurrentFluidGunIndex isn't set"))
	}
	OwnedGuns[CurrentFluidGunIndex.GetValue()].AttachedTank = TankTag;
	// Update widget with values of tank parameters.
	OnTankUpdate.Broadcast(OwnedTanks[CurrentTankIndex.GetValue()].TankData.MaxFluidAmount, OwnedTanks[CurrentTankIndex.GetValue()].TankData.FluidAmount, CurrentGun->Tank.GameplayTag);
}
```

[Back to top](#table-of-content)
