// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FG_FluidSource.generated.h"

class UWidgetComponent;
class USphereComponent;

UCLASS()
class FLUIDGUNS_API AFG_FluidSource : public AActor
{
	GENERATED_BODY()

public:
	AFG_FluidSource();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FluidSource")
	TObjectPtr<USphereComponent> SphereCollision = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FluidSource")
	TObjectPtr<UStaticMeshComponent> FluidSourceStaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FluidSource|Widget")
	TObjectPtr<UWidgetComponent> InteractionWidgetComponent = nullptr;

	// Class of interaction widget, that will be created as widget component of fluid source.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FluidSource|Widget")
	TSubclassOf<UUserWidget> InteractionWidgetClass = nullptr;
};
