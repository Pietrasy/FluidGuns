// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FG_HUD.generated.h"

class UFG_BaseWidget;
class UFG_WidgetController;
class UFG_FluidGunComponent;
class AFG_PlayerController;
class AFG_Player;

/**
 * Base class of FG_HUD.
 */
UCLASS(Abstract)
class FLUIDGUNS_API AFG_HUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category="HUD")
	TObjectPtr<AFG_Player> PlayerCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="HUD")
	TObjectPtr<AFG_PlayerController> PlayerController = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="HUD")
	TObjectPtr<UFG_FluidGunComponent> FluidGunComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="HUD")
	TObjectPtr<UFG_WidgetController> WidgetController = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="HUD")
	TObjectPtr<UFG_BaseWidget> OverlayWidget = nullptr;
	
private:
	// Blueprint class of Widget Controller, that will be created as UFG_WidgetController.
	UPROPERTY(EditDefaultsOnly, Category="HUD")
	TSubclassOf<UFG_WidgetController> WidgetControllerClass = nullptr;

	// Blueprint class of Overlay Widget, that will be general widget.
	UPROPERTY(EditDefaultsOnly, Category="HUD")
	TSubclassOf<UFG_BaseWidget> OverlayWidgetClass = nullptr;

	// Blueprint class of Fluid Gun Component to be created.
	UPROPERTY(EditDefaultsOnly, Category="HUD")
	TSubclassOf<UFG_FluidGunComponent> FluidGunComponentClass = nullptr;
};
