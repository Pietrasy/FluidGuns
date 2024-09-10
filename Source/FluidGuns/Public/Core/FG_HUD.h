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
 * HUD base class.
 */
UCLASS(Abstract)
class FLUIDGUNS_API AFG_HUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess))
	TObjectPtr<AFG_Player> PlayerCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess))
	TObjectPtr<AFG_PlayerController> PlayerController = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess))
	TObjectPtr<UFG_FluidGunComponent> FluidGunComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="HUD")
	TSubclassOf<UFG_WidgetController> WidgetControllerClass = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess))
	TObjectPtr<UFG_WidgetController> WidgetController = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="HUD")
	TSubclassOf<UFG_BaseWidget> OverlayWidgetClass = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess))
	TObjectPtr<UFG_BaseWidget> OverlayWidget = nullptr;
};
