// Copyright Pietras


#include "Widgets/FG_BaseWidget.h"

void UFG_BaseWidget::SetWidgetController(UFG_WidgetController* Controller)
{
	WidgetController = Controller;
	WidgetControllerSet();
}
