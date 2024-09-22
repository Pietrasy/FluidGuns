// Copyright Pietras


#include "Characters/FG_Player.h"

AFG_Player::AFG_Player(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.DoNotCreateDefaultSubobject(MeshComponentName))
{
	// Actor will not call Tick() every frame.
	PrimaryActorTick.bCanEverTick = false;
}