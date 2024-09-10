﻿// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FG_BaseWidget.generated.h"

class UFG_WidgetController;
/**
 * All BaseWidget derivatives can have WidgetController.
 */
UCLASS()
class FLUIDGUNS_API UFG_BaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UFG_WidgetController* Controller);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

private:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController", meta=(AllowPrivateAccess))
	TObjectPtr<UFG_WidgetController> WidgetController = nullptr;
};
