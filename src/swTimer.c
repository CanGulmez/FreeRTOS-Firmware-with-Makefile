/**
 * FreeRTOS Timer
 */

#include "main.h"

void timerCallback(TimerHandle_t timer)
{
	printLog("auto reload timer is called at %ld tick count", 
		xTaskGetTickCount());
	
	/**
	 * Other useful APIs:
	 * 
	 * void vTimerSetTimerID(const TimerHandler_t xTimer, void *pvNewID);
	 * void *vTimerSetTimerID(const TimerHandler_t xTimer);
	 * BaseType_t xTimerChangePeriod(TimerHandle_t xTimer, TickType_t xNewPeriod, 
	 * 										TickType_t xTicksToWait);
	 * BaseType_t xTimerReset(TimerHandle_t xTimer, TickType_t xTicksToWait);
	 */
}