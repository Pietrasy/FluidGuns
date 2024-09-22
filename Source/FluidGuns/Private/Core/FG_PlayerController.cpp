// Copyright Pietras


#include "Core/FG_PlayerController.h"

#include "Characters/FG_Player.h"

void AFG_PlayerController::BeginPlay()
{
	// Get controlled character and cache it as PlayerCharacter.
	PlayerCharacter = CastChecked<AFG_Player>(GetCharacter());
	Super::BeginPlay();
}
