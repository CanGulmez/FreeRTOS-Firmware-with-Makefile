/**
 * FreeRTOS Event Groups Management
 * 
 * Event groups are another feature of FreeRTOS that allow events
 * to be communicated to tasks. Unlike queues and semaphores:
 * 
 * + Event groups allow a task to wait in the Blocked state for a
 *   combination of one of more events to occur.
 * + Event groups unblock all the tasks that were waiting for the
 *   same event, or comination of events, when the event occurs.
 * 
 * These unique properties of event groups make them useful for
 * synchronizing multiple tasks, broadcasting events to more than
 * one task, allowing a task to wait in the Blocked stte for any
 * one of a set of events to occur.
 * 
 * An event flag is a boolean value used to indicate if an event
 * has occured or not. An event group is a set of event flags.
 * 
 * 	EventGroupHandle_t xEventGroupCreate(void);
 * 	EventBits_t xEventGroupSetBits(EventGroupHandle_t xEventGroup,
 * 											 const EventBits_t uxBitsToSet);
 * 
 * xEventGroupSetBits() API function sets one or more bits in an
 * event group, and is typically used to notify a task that the
 * events represented by the bit, or bits, being set has occured.
 * 
 * 	EventBits_t xEventGroupWaitBits(EventGroupHandle_t xEventGroup,
 * 											  const EventBits_t uxBitsToWaitFor,
 * 											  const BaseType_t xClearOnExit,
 * 											  const BaseType_t xWaitForAllBits,
 * 											  TickType_t xTicksToWait);
 * 
 * Existing event group --> uxBitsToWaitFor --> xWaitForAllBits
 * ------------------------------------------------------------
 * 0000 --> 0101 --> pdFALSE (ORing) --> blocked state
 * 0100 --> 0101 --> pdTRUE (ANDing) --> blocked state
 * 0100 --> 0110 --> pdFALSE (ORing) --> ready state
 * 0100 --> 0110 --> pdTRUE (ANDing) --> blocked state
 * 
 * The xEventGroupWaitBits() API function allows a task to read
 * the value of an event group, and optionally wait in the Blocked
 * state for one or more event bits in the event group to become
 * set, if the event bits are not already set.
 */

#include "main.h"

void eventTask1(void *pvParams)
{
	TickType_t ticksToWait;

	ticksToWait = pdMS_TO_TICKS(2000);
	for (;;)
	{
		vTaskDelay(ticksToWait);	/* wait for a while */

		xEventGroupSetBits(eventGroup, EVENT_TASK_BIT_0);
		printLog("eventTask1() is set the event bit 0.");

		vTaskDelay(ticksToWait);	/* wait for a while */
	}
	vTaskDelete(NULL);
}

void eventTask2(void *pvParams)
{
	TickType_t ticksToWait;

	ticksToWait = pdMS_TO_TICKS(5000);
	for (;;)
	{
		vTaskDelay(ticksToWait);	/* wait for a while */

		xEventGroupSetBits(eventGroup, EVENT_TASK_BIT_1);
		xEventGroupSetBits(eventGroup, EVENT_TASK_BIT_2);
		printLog("eventTask2() is set the event bits 1 and 2.");

		vTaskDelay(ticksToWait);	/* wait for a while */
	}
	vTaskDelete(NULL);
}

void eventTask3(void *pvParams)
{
	EventBits_t eventGroupValue;
	EventBits_t eventBitsToWait = (EVENT_TASK_BIT_0 | 
											 EVENT_TASK_BIT_1 | 
											 EVENT_TASK_BIT_2);
	for (;;)
	{
		/* Block to wait for the event bits to become set within
		 	the event group. */

		eventGroupValue = xEventGroupWaitBits(
			eventGroup,				/* event group handle */
			eventBitsToWait,		/* event bits to wait for */
			pdTRUE,					/* clear the bits on exit */
			pdTRUE,					/* wait for all bits to be set */
			portMAX_DELAY			/* wait indefinitely */
		);	

		printLog("eventTask3() is unblocked (event group value = %ld)", 
			eventGroupValue);
	}
}
