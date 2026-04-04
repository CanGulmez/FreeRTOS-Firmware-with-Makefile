/**
 * Complete FreeRTOS Tutorial
 */

#include "main.h"

/* Global and shared objects */

QueueHandle_t dataQueue;
TimerHandle_t autoReloadTimer;
TimerHandle_t oneShotTimer;
SemaphoreHandle_t binarySem;
SemaphoreHandle_t mutexSem;
TaskHandle_t notifiedTask1Handle;
EventGroupHandle_t eventGroup;

int main(void)
{
	BaseType_t res;

	HAL_Init();

	configOscClk();
	configDebugPort();

	printLog("\nThe firmware is running...");

/*****************************************************************************/
/*****************************************************************************/

	/* FreeRTOS Task Management */
	
	// res = xTaskCreate(
	// 	simpleTask1, 			/* task prototype */
	// 	"Simple Task 1",		/* task name */
	// 	256,						/* task stack depth in words */
	// 	NULL,						/* task parameter */
	// 	1,							/* task priority */
	// 	NULL						/* task payload */
	// );
	// if (res != pdPASS)
	// 	printKernel("couldn't create the simple task 1!");

	// res = xTaskCreate(simpleTask2, "Simple Task 2", 256, NULL, 1, NULL);
	// if (res != pdPASS)
	// 	printKernel("couldn't create the simple task 2!");

	// res = xTaskCreate(simpleTask3, "Simple Task 3", 256, NULL, 1, NULL);
	// if (res != pdPASS)
	// 	printKernel("couldn't create the simple task 3!");

	// res = xTaskCreate(simpleTask4, "Simple Task 4", 256, NULL, 1, NULL);
	// if (res != pdPASS)
	// 	printKernel("couldn't create the simple task 4!");
	
/*****************************************************************************/
/*****************************************************************************/

	/* FreeRTOS Queue Management */

	// dataQueue = xQueueCreate(1, 2 * sizeof(Data_t));
	// if (dataQueue == NULL)
	// {
	// 	printKernel("couldn't create the queue!");
	// }
	// else
	// {
	// 	res = xTaskCreate(senderTask, "Sender Task", 256, NULL, 1, NULL);
	// 	if (res != pdPASS)
	// 		printKernel("couldn't create the sender task!");

	// 	res = xTaskCreate(receiverTask, "Receiver Task", 256, NULL, 1, NULL);
	// 	if (res != pdPASS)
	// 		printKernel("couldn't create the receiver task!");			
	// }

/*****************************************************************************/
/*****************************************************************************/

	/* FreeRTOS Software Timer Management */

	// autoReloadTimer = xTimerCreate(
	// 	"Auto Reload Timer",				/* timer name */
	// 	pdMS_TO_TICKS(3000),				/* timer period */
	// 	pdTRUE,								/* timer is auto reload */
	// 	(void *) 10,						/* timer ID */
	// 	autoReloadTimer1					/* timer callback */
	// );
	// if (autoReloadTimer == NULL)
	// 	printKernel("couldn't create auto reload timer!");

	// oneShotTimer = xTimerCreate(
	// 	"One Shot Timer", 
	// 	pdMS_TO_TICKS(5000),
	// 	pdFALSE, 
	// 	(void *) 20, 
	// 	oneShotTimer2
	// );
	// if (oneShotTimer == NULL)
	// 	printKernel("couldn't create one shot timer!");

	// res = xTimerStart(autoReloadTimer, 0);
	// if (res != pdPASS)
	// 	printKernel("couldn't start the auto reload timer!");
	// else
	// 	printLog("auto reload timer is started...");

	// res = xTimerStart(oneShotTimer, 0);
	// if (res != pdPASS)
	// 	printKernel("couldn't start the one shot timer!");	
	// else
	// 	printLog("one shot timer is started...");

/*****************************************************************************/
/*****************************************************************************/

	/* FreeRTOS Interrupt Management */

	// binarySem = xSemaphoreCreateBinary();
	// if (binarySem == NULL)
	// 	printKernel("couldn't create the binary semaphore!");

	// res = xTaskCreate(syncTask1, "Sync Task 1", 256, NULL, 3, NULL);
	// if (res != pdPASS)
	// 	printKernel("couldn't create the sync task 1!");

	// res = xTaskCreate(syncTask2, "Sync Task 2", 256, NULL, 1, NULL);
	// if (res != pdPASS)
	// 	printKernel("couldn't create the sync task 2!");

/*****************************************************************************/
/*****************************************************************************/

	/* FreeRTOS Resource Management */

	// mutexSem = xSemaphoreCreateMutex();
	// if (mutexSem == NULL)
	// 	printKernel("couldn't create the mutex semaphore!");

	// res = xTaskCreate(resourceTask1, "Resource Task 1", 256, NULL, 1, NULL);
	// if (res != pdPASS)
	// 	printKernel("couldn't create the release task 1!");

	// res = xTaskCreate(resourceTask2, "Resource Task 2", 256, NULL, 1, NULL);
	// if (res != pdPASS)
	// 	printKernel("couldn't create the release task 2!");

/*****************************************************************************/
/*****************************************************************************/

	/* FreeRTOS Event Group Management */

	eventGroup = xEventGroupCreate();
	if (eventGroup == NULL)
		printKernel("couldn't create the event group!");
		
	res = xTaskCreate(eventTask1, "Event Task 1", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the event task 1!");

	res = xTaskCreate(eventTask2, "Event Task 2", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the event task 2!");

	res = xTaskCreate(eventTask3, "Event Task 3", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the event task 3!");
	
/*****************************************************************************/
/*****************************************************************************/

	/**
	 * FreeRTOS Task Notification Management
	 *
	 * There is no need to create a task notification object.
	 */

	// res = xTaskCreate(notifiedTask1, "Notified Task 1", 256, NULL, 1, 
	// 	&notifiedTask1Handle);
	// if (res != pdPASS)
	// 	printKernel("couldn't create the notified task 1!");

	// res = xTaskCreate(notifiedTask2, "Notified Task 2", 256, NULL, 1, NULL);
	// if (res != pdPASS)
	// 	printKernel("couldn't create the notified task 2!");

/*****************************************************************************/
/*****************************************************************************/

	printLog("%d bytes free heap size", xPortGetFreeHeapSize());

	vTaskStartScheduler();

	while (1);
}
