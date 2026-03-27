/**
 * FreeRTOS Interrupt Management
 * 
 * Embedded real-time systems have to take actions in response to
 * events that originate from the environment.
 * 
 * It is important to draw a distinction between the priority of
 * a task, and the priority of an interrupt:
 * 
 * + A task is a software feature that is unrelated to the 
 *   hardware on which FreeRTOS is running. The priority of a 
 *   task is assigned in software by the application writer, 
 *   and a software algorithm decides which task will be placed
 *   in the Running state.
 * 
 * + Although written in software, an interrupt service routine
 *   is a hardware feature because the hardware controls which
 *   interrupt service routine will run, and when it will run.
 *   Tasks will only run when there are no ISRs running, so the
 *   lowest priority interrupt will interrupt will interrupt
 *   the highest priority task, and there is no way for a task
 *   to pre-empt an ISR.
 * 
 * Note: Never call a FreeRTOS API function that does not have
 * 		"FromISR" in its name from an ISR.
 * 
 *	taskYIELD() is a macro that can be called in a task to request
 * a context switch.
 * 
 * It is normally considered best practice to keep ISRs as short
 * as possible.
 * 
 * Before a semphore can be used, it must be creates. To create
 * a binary semaphore:
 * 
 * 	SemaphoreHandle_t xSemaphoreCreateBinary(void);
 * 
 * Taking a semaphore means to obtain or receive the semaphore.
 * 
 * 	BaseType_t xSemaphoreTake(SemaphoreHandle_t xSemaphore,
 * 									  TickType_t xTicksToWait);
 */

#include "main.h"

void syncTask1(void *pvParams)
{
	BaseType_t res;

	for (;;)
	{
		printLog("syncTask1() started here...");

		res = xSemaphoreTake(binarySemaphore, portMAX_DELAY);
		if (res != pdPASS)
			printKernel("semaphore cannot be taken from syncTask1()!");

		printLog("doing the task stuffs...");

		vTaskDelay(pdMS_TO_TICKS(2000));	/* delay in ms */
	}
	vTaskDelete(NULL);
}

void syncTask2(void *pvParams)
{
	BaseType_t res;

	for (;;)
	{
		printLog("syncTask2() started here...");

		vTaskDelay(pdMS_TO_TICKS(5000));	/* delay in ms */

		res = xSemaphoreGive(binarySemaphore);
		if (res != pdPASS)
			printKernel("semaphore cannot be given from syncTask2()!");
			
		vTaskDelay(pdMS_TO_TICKS(3000));	/* delay in ms */
	}
	vTaskDelete(NULL);
}

