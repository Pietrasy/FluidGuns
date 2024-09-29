# Fluid Guns
The project is based on a system for managing fluid guns, which allows the addition of guns, gun addons and fluid tanks.
<br />Guns and tanks can be spawned by a spawner and picked up by the player, and tanks are refilled at fluid sources.


[Step](#creating-fluid-gun-data-asset)
[Step2](#creating-tank-data-asset)
[Step3](#creating-addon)
[Step4](#crating-dluid-source)

## Creating fluid gun data asset.
Creating a data asset, inheriting from the FG_PDA_FluidGun and set parameters and properties of the gun.
![Creating Fluid Gun DA](https://github.com/user-attachments/assets/5e0ef761-0efa-46d8-bce2-4aa3daf65730)
![2  Setup Fluid Gun DA 2](https://github.com/user-attachments/assets/a2d98cfb-e4cb-4703-86a3-cc33693c40ad)
<br /><br />If [created an addon](#Creating-Addon), we can add it to the gun.<br />
![4  Set Addon](https://github.com/user-attachments/assets/e9b831d3-6622-4eb4-b3cd-fd7584866631)
<br /><br />Action determines what function is to be performed when the item is picked up.<br />
![4  Set Addon](https://github.com/user-attachments/assets/915da8f0-f512-4f64-8a46-9afa3398d216)

## Creating tank data asset.
Creating a data asset, inheriting from the FG_PDA_Tank and set parameters and properties of the tank.
![5  Creating Tank DA](https://github.com/user-attachments/assets/525d818b-9075-4e7b-9b3f-0c179fd81d5e)
![6  Setup Tank DA 2](https://github.com/user-attachments/assets/5d3de5a7-9f50-4c63-89cf-be161bdc0965)

## Place **BP_Spawner** at level and set item to spawn. 
![7  Set DA on Spawner](https://github.com/user-attachments/assets/8fc9eeb7-6fcc-4d54-be34-de8ebb5258f7)

## Creating Addon.
Create a blueprint class of **BP_Addons** and set its properties.
![8  Creating child addon](https://github.com/user-attachments/assets/83dd2227-3993-49d6-be71-30d115007ca6)
![9  Setup addon](https://github.com/user-attachments/assets/c27b2174-c81c-4673-b102-c029b8fd27b7)

## Creating Fluid Source.
Place **BP_FluidSource** at level and set gameplay tag of fluid type.
![10  Set fluid type to Fluid Source](https://github.com/user-attachments/assets/406c7631-3567-469a-bbdd-3c5bbaf4a516)
<br /><br />Add new row in **DT_FluidColors** and choose color for gameplay tag.
![11  Add Fluid to DT](https://github.com/user-attachments/assets/403c649c-1b91-44da-bd34-24fa2530724e)

## Set a slot for the new fluid gun.
Add input to **IMC_FluidGunComponent**
![12  Adding input to IMC](https://github.com/user-attachments/assets/8c5d452c-9633-4210-b1cd-ce88b0bd90a1)
<br /><br />Handle input for the new slot in **BP_FluidGunComponent**
![13  Set up input](https://github.com/user-attachments/assets/bb2d272f-c172-4c39-a112-9b1698185f96)
