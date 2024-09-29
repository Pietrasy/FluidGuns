# Fluid Guns
This project is based on a system for managing fluid guns, allowing for the addition of new guns, gun addons, and fluid tanks. Guns and tanks can be spawned by a spawner, picked up by the player, and refilled at fluid sources.
<br />

### Table of Content:
[Creating a Fluid Gun Data Asset](#creating-a-fluid-gun-data-asset)<br />
[Creating a Tank Data Asset](#creating-a-tank-data-asset)<br />
[Setting Up Spawner](#setting-up-spawner)<br />
[Creating an Addon](#creating-an-addon)<br />
[Creating a Fluid Source](#creating-a-fluid-source)<br />
[Set Up a Slot for the New Fluid Gun](#set-up-a-slot-for-the-new-fluid-gun)<br />

## Creating a Fluid Gun Data Asset.
Create a data asset that inherits from **FG_PDA_FluidGun**, and set the parameters and properties of the gun.<br />
![Creating Fluid Gun DA](https://github.com/user-attachments/assets/5e0ef761-0efa-46d8-bce2-4aa3daf65730)
![2  Setup Fluid Gun DA 2](https://github.com/user-attachments/assets/a2d98cfb-e4cb-4703-86a3-cc33693c40ad)
<br />If an [addon is created](#creating-an-addon), it can be added to the gun.<br />
![4  Set Addon](https://github.com/user-attachments/assets/e9b831d3-6622-4eb4-b3cd-fd7584866631)
<br />The action determines which function is performed when the item is picked up.<br />
![3  Set Action](https://github.com/user-attachments/assets/433a7d5f-5a9d-4bf6-8a26-23e0c89f3c7c)


[Back to top](#table-of-content)

## Creating a Tank Data Asset.
Create a data asset that inherits from **FG_PDA_Tank** and set the parameters and properties of the tank.<br />
![5  Creating Tank DA](https://github.com/user-attachments/assets/525d818b-9075-4e7b-9b3f-0c179fd81d5e)
![6  Setup Tank DA 2](https://github.com/user-attachments/assets/5d3de5a7-9f50-4c63-89cf-be161bdc0965)

[Back to top](#table-of-content)

## Setting Up Spawner. 
Place the **BP_Spawner** in the level and set the item to spawn.<br />
![7  Set DA on Spawner](https://github.com/user-attachments/assets/a1e80835-6414-4a1d-8d37-41421dc2666c)


[Back to top](#table-of-content)

## Creating an Addon.
Create a blueprint class for **BP_Addons** and configure its properties.<br />
![8  Creating child addon](https://github.com/user-attachments/assets/83dd2227-3993-49d6-be71-30d115007ca6)
![9  Setup addon](https://github.com/user-attachments/assets/c27b2174-c81c-4673-b102-c029b8fd27b7)

[Back to top](#table-of-content)

## Creating a Fluid Source.
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

