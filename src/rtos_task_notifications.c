/**
 * FreeRTOS Task Notifications
 * 
 * FreeRTOS applications are typically structured as a series 
 * of independent tasks that communicate with each other to 
 * provide the system functionality. Task notifications are an
 * efficient mechanism allowing one task to directly notify
 * another task.
 * 
 * Task notifications allow tasks to interact with other tasks,
 * and to synchronize with ISRs, without the need for a separate
 * communication object.
 * 
 * This wide range of usage scenarios can be achieved by using
 * the xTaskNotify() API to send a task notification, and the
 * xTaskNotifyWait() API function to receive a task notification.
 * 
 * 	BaseType_t xTaskNotifyGive(TaskHandle_t xTaskToNotify);
 * 	uint32_t ulTaskNotifyTake(BaseType_t xClearCountOnExit,
 * 									  TickType_t xTicksToWait);
 * 
 * Using a task notification to send an event or data to a task
 * is significantly faster than using a queue, semaphore or event
 * group to perform an equivalent operation.
 * 
 * But task notifications cannot be used in all scenarios:
 * 
 * + Sending an event or data to an ISR.
 * + Enable more than one receiving task.
 * + Buffering multiple data items.
 * + Broadcasting to more than one task.
 * + Waiting in the blocked state for a send to complete.
 * 
 * xTaskNotifyGive() sends a notification directly to a task, and
 * increments the receiving task's notification value. Calling
 * xNotifyGive() will set the receiving task's notification to
 * pending, it was not already pending.
 * 
 * ulTaskNotifyTake() allows a task to wait in the Blocked state
 * for its notification value to be greater than zero.
 */

#include "main.h"

void notifiedTask1(void *pvParams)
{
	uint32_t isNotified = 0;

	for (;;)
	{
		printLog("notifiedTask1() is waiting for a notification...");

		/* Wait to receive a notification sent directly to this task. */
		isNotified = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		if (isNotified)
		{
			printLog("notifiedTask1() received a notification");
		}
	}	
	vTaskDelete(NULL);
}

void notifiedTask2(void *pvParams)
{
	BaseType_t res;
	const TickType_t blockTime = pdMS_TO_TICKS(2000);

	for (;;)
	{
		/* Wait a bit... */
		vTaskDelay(blockTime);
	
		/**
		 * Notify the other task by sending a notification directly to it.
		 * The receiving task's notification value will be incremented.
		 */
		res = xTaskNotifyGive(notifiedTask1Handle);
		if (res != pdPASS)
			printKernel("couldn't send the notification!");
		else
			printLog("the notification is sent to notifiedTask1()");
	}
	vTaskDelete(NULL);
}
