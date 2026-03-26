/**
 * FreeRTOS Queue Management
 * 
 * Queues provide a task-to-task, task-to-interrupt, and 
 * interrupt-to-task communication mechanism.
 * 
 * A queue can hold a finite number of fixed size data items.
 * 
 * Queues are normally used as First In First Out (FIFO) buffers,
 * where data is written to the end of the queue and remved from
 * the from of the queue.
 * 
 * Any number of tasks can write to the same queue, and any number
 * of tasks can read from the same queue. In practice, it is very
 * common for a queue to have multiple writers, but much less
 * common for a queue to have multiple readers.
 * 
 * When a task attempts to read from a queue, it can optionally
 * specify a "block" time. This is the time the task is kept in
 * the Blocked state to wait for data to become available from
 * the queue.
 * 
 * 	QueueHandle_t xQueueCreate(UBaseType_t uxQueueLength,
 * 										UBaseType_t uxItemSize);
 * 	BaseType_t xQueueSendToBack(QueueHandle_t xQueue,
 * 										 const void *pvItemToQueue,
 * 										 TickType_t xTicksToWait);
 * 	BaseType_t xQueueSendToFront(QueueHandle_t xQueue,
 * 										  const void *pvItemToQueue,
 * 										  TickType_t xTicksToWait);
 * 	BaseType_t xQueueReceive(QueueHandle_t xQueue,
 * 									 void * const pvBuffer,
 * 									 TickType_t xTicksToWait);
 * 	uxQueueMessagesWaiting(QueueHandle_t xQueue);
 * 
 * It is common in FreeRTOS designs for a task to receive data
 * from more than one source. The receiving task needs to know
 * where the data came from to determine what to do with it.
 */

#include "main.h"

/* Declare two variables of type Data_t that will be passed
	on the queue. */
static const Data_t queueData[2] = {
	{100, eSender1},	
	{200, eSender2}
};

void senderTask(void *pvParams)
{
	BaseType_t res;

	for (;;)
	{
		res = xQueueSend(queue, queueData, 0);
		if (res != pdPASS)
			printKernel("couldn't send the value to queue!");
		else
			printLog("the structured data was sent to queue");

		vTaskDelay(pdMS_TO_TICKS(2000));	/* delay in ms */
	}
	vTaskDelete(NULL);
}

void receiverTask(void *pvParams)
{
	BaseType_t res;
	Data_t receivedData[2];
	TickType_t waitTick;

	waitTick = pdMS_TO_TICKS(50);
	for (;;)
	{
		if (uxQueueMessagesWaiting(queue) == 0)
		{
			printKernel("queue shouldn't have been empty!");
		}
		else
		{
			res = xQueueReceive(queue, receivedData, waitTick);
			if (res != pdPASS)
				printKernel("couldn't receive the value from queue!");
			else
				printLog("eSender1: %d, eSender2: %d", 
					receivedData[0].pValue, receivedData[1].pValue);
		}

		vTaskDelay(pdMS_TO_TICKS(2100));	/* delay in ms */
	}
	vTaskDelete(NULL);
}
 