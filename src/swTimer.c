/**
 * FreeRTOS Timer Management
 * 
 * Software timers are used to schedule the execution of a
 * function at a set time in the future, or periodically with
 * a fixed frequency. The function executed by the software
 * timer is called the software timer's callback function.
 * 
 * Software timers are implemented by, and are under the control
 * of, the FreeRTOS kernel, They do not require hardware support,
 * and are not related to hardware timers or hardware counters.
 * 
 * Software timer callback functions as C functions. The only
 * thing special about them is their prototype, which must 
 * return void, and take a handle to a software timer as its only
 * parameter.
 * 
 * 	void ATimerCallback(TimerHandle_t xTimer);
 * 
 * There are two types of software timer:
 * 
 * + One-shot timers:
 * 	Once started, a one-shot timer will execute its callback
 * 	function once only.
 * + Auto-reload timers:
 * 	Once started, an auto-reload timer will re-start itself 
 * 	each time it expires, resulting in periodic execution of 
 * 	its callback function.
 * 
 * 	BaseType_t xTimerDelete(TimerHandle_t xTimer, 
 * 									TickType_t xTicksToWait);
 * 
 * Software timers can be created before the scheduler is running,
 * or from a task after the schedular has been started.
 * 
 * 	TimerHandle_t xTimerCreate(const char *const pcTimerName,
 * 										const TickType_t xTimerPeriodTicks,
 * 										const BaseType_t xAutoReload,
 * 										void *const pvTimerID,
 * 										TimerCallbackFunction_t pxCallback);
 * 	BaseType_t xTimerStart(TimerHandle_t xTimer, 
 * 								  TickType_t xTicksToWait);
 * 
 * Each software timer has an ID, which is a tag value that can be
 * used by the application writer for any purpose. The ID is stored
 * in a void pointer, so it can store any integer value directly.
 * 
 * 	void vTimerSetTimerID(const TimerHandler_t xTimer, 
 * 								 void *pvNewID);
 * 	void *vTimerGetTimerID(const TimerHandler_t xTimer);
 * 
 * The period of a software timer is changed using these APIs.
 * 
 * 	BaseType_t xTimerChangePeriod(TimerHandle_t xTimer, 
 * 											TickType_t xNewPeriod, 
 * 											TickType_t xTicksToWait);
 * 	BaseType_t xTimerReset(TimerHandle_t xTimer, 
 * 								  TickType_t xTicksToWait);
 * 
 * Resetting a software timer means to re-start the timer; the
 * timer's expiry time is recalculated to be relative to when 
 * the timer was reset, rather than when the timer was originally
 * started.
 * 
 * 	BaseType_t xTimerReset(TimerHandle_t xTimer, 
 * 								  TickType_t xTicksToWait);
 */

#include "main.h"

void autoReloadTimerCallback(TimerHandle_t xTimer)
{
	int autoReloadTimerID;

	/* Get the auto reload timer ID */
	autoReloadTimerID = (int) pvTimerGetTimerID(xTimer);

	printLog("auto reload timer (ID = %d) is called at %ld tick count", 
		autoReloadTimerID, xTaskGetTickCount());

	/* Change the auto reload timer period. */
	/* xTimerChangePeriod(xTimer, pdMS_TO_TICKS(2000), 0); */
}

void oneShotTimerCallback(TimerHandle_t xTimer)
{
	int oneShotTimerID;

	/* Get the one shot timer ID */
	oneShotTimerID = (int) pvTimerGetTimerID(xTimer);

	printLog("one shot timer (ID = %d) is called at %ld tick count", 
		oneShotTimerID, xTaskGetTickCount());

	/* Change the one shot timer period. */
	/* xTimerChangePeriod(xTimer, pdMS_TO_TICKS(6000), 0); */
}
