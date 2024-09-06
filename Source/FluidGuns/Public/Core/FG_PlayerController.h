// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FG_PlayerController.generated.h"

class AFG_Player;
/**
 * Player Controller base class
 */
UCLASS(Abstract)
class FLUIDGUNS_API AFG_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, Category="PlayerController")
	TObjectPtr<AFG_Player> PlayerCharacter;
};
