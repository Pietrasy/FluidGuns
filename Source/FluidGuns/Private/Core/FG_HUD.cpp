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
	PlayerController = CastChecked<AFG_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerCharacter = CastChecked<AFG_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FluidGunComponent = PlayerCharacter->GetComponentByClass<UFG_FluidGunComponent>();

	PlayerController->SetInputMode(FInputModeGameOnly());

	WidgetController = NewObject<UFG_WidgetController>(this, WidgetControllerClass);
	
	OverlayWidget = CreateWidget<UFG_BaseWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->SetWidgetController(WidgetController);
	OverlayWidget->AddToViewport();
	
	Super::BeginPlay();
}
