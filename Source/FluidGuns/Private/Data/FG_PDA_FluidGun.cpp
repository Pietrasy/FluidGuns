// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/FG_PDA_FluidGun.h"

void UFG_PDA_FluidGun::PostLoad()
{
	Super::PostLoad();

	FluidGunData.Pressure = FluidGunData.MaxPressure;
	FluidGunData.Range = (FluidGunData.BaseRange * FluidGunData.Pressure) / 50;
}
