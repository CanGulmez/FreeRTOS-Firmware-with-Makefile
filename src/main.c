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
TaskHandle_t notifiedTaskHandle;
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

	res = xTaskCreate(
		rtosTask1, 			/* task prototype */
		"Simple Task 1",		/* task name */
		256,						/* task stack depth in words */
		NULL,						/* task parameter */
		1,							/* task priority */
		NULL						/* task payload */
	);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 1!");

	res = xTaskCreate(rtosTask2, "RTOS Task 2", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 2!");

	res = xTaskCreate(rtosTask3, "RTOS Task 3", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 3!");

	res = xTaskCreate(rtosTask4, "RTOS Task 4", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 4!");
	
/*****************************************************************************/
/*****************************************************************************/

	/* FreeRTOS Queue Management */

	dataQueue = xQueueCreate(1, 2 * sizeof(Data_t));
	if (dataQueue == NULL)
		printKernel("couldn't create the queue!");

	res = xTaskCreate(rtosTask5, "RTOS Task 5", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 5!");

	res = xTaskCreate(rtosTask6, "RTOS Task 6", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 6!");			

/*****************************************************************************/
/*****************************************************************************/

	/* FreeRTOS Software Timer Management */

	autoReloadTimer = xTimerCreate(
		"Auto Reload Timer",				/* timer name */
		pdMS_TO_TICKS(3000),				/* timer period */
		pdTRUE,								/* timer is auto reload */
		(void *) 10,						/* timer ID */
		rtosTask7							/* timer callback */
	);
	if (autoReloadTimer == NULL)
		printKernel("couldn't create rtos task 7!");

	oneShotTimer = xTimerCreate(
		"One Shot Timer", 
		pdMS_TO_TICKS(5000),
		pdFALSE, 
		(void *) 20, 
		rtosTask8
	);
	if (oneShotTimer == NULL)
		printKernel("couldn't create rtos task *!");

	res = xTimerStart(autoReloadTimer, 0);
	if (res != pdPASS)
		printKernel("couldn't start the rtos task 7!");

	res = xTimerStart(oneShotTimer, 0);
	if (res != pdPASS)
		printKernel("couldn't start the rtos task 8!");	

/*****************************************************************************/
/*****************************************************************************/

	/* FreeRTOS Interrupt Management */

	binarySem = xSemaphoreCreateBinary();
	if (binarySem == NULL)
		printKernel("couldn't create the binary semaphore!");
	
	res = xTaskCreate(rtosTask9, "RTOS Task 9", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 9!");

	res = xTaskCreate(rtosTask10, "RTOS Task 10", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 10!");

/*****************************************************************************/
/*****************************************************************************/

	/* FreeRTOS Resource Management */

	mutexSem = xSemaphoreCreateMutex();
	if (mutexSem == NULL)
		printKernel("couldn't create the mutex semaphore!");

	res = xTaskCreate(rtosTask11, "RTOS Task 11", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 11!");

	res = xTaskCreate(rtosTask12, "RTOS Task 12", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 12!");

/*****************************************************************************/
/*****************************************************************************/

	/* FreeRTOS Event Group Management */

	eventGroup = xEventGroupCreate();
	if (eventGroup == NULL)
		printKernel("couldn't create the event group!");
		
	res = xTaskCreate(rtosTask13, "RTOS Task 13", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 13!");

	res = xTaskCreate(rtosTask14, "RTOS Task 14", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 14!");

	res = xTaskCreate(rtosTask15, "RTOS Task 15", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 15!");
	
/*****************************************************************************/
/*****************************************************************************/

	/**
	 * FreeRTOS Task Notification Management
	 *
	 * There is no need to create a task notification object.
	 */

	res = xTaskCreate(rtosTask16, "RTOS Task 16", 256, NULL, 1, 
		&notifiedTaskHandle);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 16!");

	res = xTaskCreate(rtosTask17, "RTOS Task 17", 256, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the rtos task 17!");

/*****************************************************************************/
/*****************************************************************************/

	printLog("%d bytes free heap size", xPortGetFreeHeapSize());

	vTaskStartScheduler();

	while (1);
}
 