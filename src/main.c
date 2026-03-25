/**
 * Complete FreeRTOS Tutorials
 */

#include "main.h"

int main(void)
{
	BaseType_t res;

	HAL_Init();

	configOscClk();
	configDebugPort();

	printLog("\rThe firmware is running...");

/*****************************************************************************/
/*****************************************************************************/

	/* Create the simple tasks. */

	res = xTaskCreate(
		simpleTask1, 			/* task prototype */
		"Simple Task 1",		/* task name */
		512,						/* task stack depth in words */
		NULL,						/* task parameter */
		1,							/* task priority */
		NULL						/* task payload */
	);
	if (res != pdPASS)
		printKernel("couldn't create the simple task 1!");

	res = xTaskCreate(simpleTask2, "Simple Task 2", 512, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the simple task 2!");

	res = xTaskCreate(simpleTask3, "Simple Task 3", 512, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the simple task 3!");

	res = xTaskCreate(simpleTask4, "Simple Task 4", 512, NULL, 1, NULL);
	if (res != pdPASS)
		printKernel("couldn't create the simple task 4!");
	
/*****************************************************************************/
/*****************************************************************************/

	// queue = xQueueCreate(5, sizeof(int32_t));
	// if (queue == NULL)
	// {
	// 	printKernel("couldn't create the queue!");
	// }
	// else
	// {
	// 	res = xTaskCreate(senderTask, "Sender Task", 512, NULL, 1, NULL);
	// 	if (res != pdPASS)
	// 		printKernel("couldn't create the sender task!");

	// 	res = xTaskCreate(receiverTask, "Receiver Task", 512, NULL, 1, NULL);
	// 	if (res != pdPASS)
	// 		printKernel("couldn't create the receiver task!");			
	// }

/*****************************************************************************/
/*****************************************************************************/

	// timer = xTimerCreate(
	// 	"Auto Reload Timer",			/* timer name */
	// 	pdMS_TO_TICKS(3000),			/* timer period */
	// 	pdTRUE,							/* timer is auto reload */
	// 	NULL,								/* timer ID */
	// 	timerCallback					/* timer callback */
	// );
	// if (timer == NULL)
	// 	printKernel("couldn't create auto reload timer!");

	// res = xTimerStart(timer, 0);
	// if (res != pdPASS)
	// 	printKernel("couldn't start the auto reload timer!");

/*****************************************************************************/
/*****************************************************************************/

	

/*****************************************************************************/
/*****************************************************************************/

	printLog("%d bytes free heap size", xPortGetFreeHeapSize());

	vTaskStartScheduler();

	while (1);
}
