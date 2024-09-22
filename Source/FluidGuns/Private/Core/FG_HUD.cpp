// Copyright Pietras


#include "Core/FG_HUD.h"

#include "Blueprint/UserWidget.h"
#include "Characters/FG_Player.h"
#include "Core/FG_PlayerController.h"
#include "Components/FG_FluidGunComponent.h"
#include "Widgets/FG_BaseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/FG_WidgetController.h"

void AFG_HUD::BeginPlay()
{
	// Cache player controller, player character and fluid gun component.
	PlayerController = CastChecked<AFG_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerCharacter = CastChecked<AFG_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FluidGunComponent = PlayerCharacter->GetComponentByClass<UFG_FluidGunComponent>();
	//Set input mode to Game Only, so thath PIE catches focus immediately.
	PlayerController->SetInputMode(FInputModeGameOnly());
	// Create WidgetController.
	WidgetController = NewObject<UFG_WidgetController>(this, WidgetControllerClass);
	// Create overlay widget and add it to viewport.
	OverlayWidget = CreateWidget<UFG_BaseWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->SetWidgetController(WidgetController);
	OverlayWidget->AddToViewport();
	Super::BeginPlay();
}