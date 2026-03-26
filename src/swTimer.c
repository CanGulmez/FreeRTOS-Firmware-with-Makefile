/**
 * FreeRTOS Timer Management
 */

#include "main.h"

void autoReloadTimerCallback(TimerHandle_t timer)
{
	printLog("auto reload timer is called at %ld tick count", 
		xTaskGetTickCount());
}

void oneShotTimerCallback(TimerHandle_t timer)
{
	printLog("one shot timer is called at %ld tick count", 
		xTaskGetTickCount());
}
