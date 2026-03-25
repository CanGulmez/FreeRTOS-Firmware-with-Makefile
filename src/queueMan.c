/**
 * FreeRTOS Queue Management
 */

#include "main.h"

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

		vTaskDelay(pdMS_TO_TICKS(2000));	/* delay in ms */
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

		vTaskDelay(pdMS_TO_TICKS(2100));	/* delay in ms */
	}
	vTaskDelete(NULL);
}
