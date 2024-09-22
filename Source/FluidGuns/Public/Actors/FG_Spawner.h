// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FG_Spawner.generated.h"

class USphereComponent;
class UArrowComponent;
class UFG_PDA_Item;

UCLASS()
class FLUIDGUNS_API AFG_Spawner : public AActor
{
	GENERATED_BODY()

public:
	AFG_Spawner();

	// Data asset of item to spawn.
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Spawner")
	TSoftObjectPtr<UFG_PDA_Item> ItemToSpawn = nullptr;

	// Static mesh component to show spawned item.
	UPROPERTY(BlueprintReadOnly, Category="Spawner")
	TObjectPtr<UStaticMeshComponent> ItemStaticMesh = nullptr;
	
private:
	// Arrow component to indicate front of spawner.
	UPROPERTY(VisibleDefaultsOnly, Category="Spawner")
	TObjectPtr<UArrowComponent> ArrowComponent = nullptr;

	// Sphere component as collision for spawner.
	UPROPERTY(VisibleDefaultsOnly, Category="Spawner")
	TObjectPtr<USphereComponent> SphereCollision = nullptr;
};
