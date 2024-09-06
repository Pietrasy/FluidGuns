// Copyright Pietras


#include "Core/FG_PlayerController.h"

#include "Characters/FG_Player.h"

void AFG_PlayerController::BeginPlay()
{
	// Get controlled character.
	PlayerCharacter = CastChecked<AFG_Player>(GetCharacter());
	
	Super::BeginPlay();
}
