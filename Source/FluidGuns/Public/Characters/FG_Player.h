// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Interfaces/FG_ActionInterface.h"
#include "FG_Player.generated.h"

UCLASS()
class FLUIDGUNS_API AFG_Player : public ACharacter, public IFG_ActionInterface
{
	GENERATED_BODY()

public:
	// Constructor to disable create skeletal mesh.
	AFG_Player(const FObjectInitializer& ObjectInitializer);

	// Gameplay tag of character.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player")
	FGameplayTagContainer CharacterGameplayTag = FGameplayTagContainer::EmptyContainer;
};
