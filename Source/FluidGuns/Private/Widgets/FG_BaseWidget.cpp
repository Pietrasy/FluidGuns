// Copyright Pietras


#include "Widgets/FG_BaseWidget.h"

void UFG_BaseWidget::SetWidgetController(UFG_WidgetController* Controller)
{
	// Cache WidgetController and call WidgetControllerSet event.
	WidgetController = Controller;
	WidgetControllerSet();
}
