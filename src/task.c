/**
 * FreeRTOS Task Implementations
 */

#include "main.h"

QueueHandle_t queue;
TimerHandle_t timer;

void simpleTask1(void *pvParameters)
{
	int32_t localVar = 0;

	for (;;)
	{
		printLog("simple task 1: %ld", localVar++);

		vTaskDelay(pdMS_TO_TICKS(9000));	/* delay in seconds */
	}
	vTaskDelete(NULL);
}

void simpleTask2(void *pvParameters)
{
	int32_t localVar = 0;

	for (;;)
	{
		printLog("simple task 2: %ld", localVar++);
		
		vTaskDelay(pdMS_TO_TICKS(10000));	/* delay in seconds */
	}
	vTaskDelete(NULL);
}

/*****************************************************************************/
/*****************************************************************************/

extern void senderTask(void *pvParameters)
{
	int32_t value;
	BaseType_t res;

	/* Just send the random value. */
	srand((unsigned int) xTaskGetTickCount());

	for (;;)
	{
		value = rand() % 100;

		res = xQueueSend(queue, &value, 0);
		if (res != pdPASS)
			printKernel("couldn't send the value to queue!");
		else
			printLog("the value (%ld) was sent to queue", value);

		vTaskDelay(pdMS_TO_TICKS(2000));	/* delay in seconds */
	}
	vTaskDelete(NULL);
}

extern void receiverTask(void *pvParameters)
{
	int32_t value;
	BaseType_t res;

	for (;;)
	{
		if (uxQueueMessagesWaiting(queue) == 0)
			printKernel("queue shouldn't have been empty!");

		res = xQueueReceive(queue, &value, pdMS_TO_TICKS(50));
		if (res != pdPASS)
			printKernel("couldn't receive the value from queue!");
		else
			printLog("received = %ld", value);

		vTaskDelay(pdMS_TO_TICKS(2100));	/* delay in seconds */
	}
	vTaskDelete(NULL);
}

/*****************************************************************************/
/*****************************************************************************/

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

/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
/*****************************************************************************/

void vApplicationIdleHook(void)
{
	__WFI();
}
