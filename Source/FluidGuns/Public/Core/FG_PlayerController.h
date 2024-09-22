// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FG_PlayerController.generated.h"

class AFG_Player;
/**
 * Base class of FG_Player Controller.
 */
UCLASS(Abstract)
class FLUIDGUNS_API AFG_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, Category="PlayerController")
	TObjectPtr<AFG_Player> PlayerCharacter = nullptr;
};
