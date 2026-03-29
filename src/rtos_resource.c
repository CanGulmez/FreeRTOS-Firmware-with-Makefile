/**
 * FreeRTOS Resource Management
 * 
 * In a multitasking system, there is potential for error if one 
 * task starts to access a resource, but does not complete its 
 * access before being transitioned out of the Running. If the 
 * task leaves the resource in a inconsistent state, then access 
 * to the same resource by one any other task or interrupt could 
 * result in data corruption.
 * 
 * Basic critical sections are regions of code that are surrounded
 * by calls to the macros taskENTER_CRITICAL(), taskEXIT_CRITICAL
 * respectively.
 * 
 * 	BaseType_t xTaskSuspendAll(void);
 * 	BaseType_t xTaskResumeAll(void);
 * 
 * A mutex is a special type of binary semaphore that is used to
 * control access to a resource that is shared between two or more
 * tasks.
 * 
 * 	SemaphoreHandle_t xSemaphoreCreateMutex(void);
 */

#include "main.h"

int sharedResource[SHARED_RESOURCE];

void resourceTask1(void *pvParams)
{
	int i;
	BaseType_t res;

	for (;;)
	{
		/* Update the shared resource with random values */
		res = xSemaphoreTake(mutexSem, portMAX_DELAY);
		if (res == pdTRUE)
		{
			for (i = 0; i < SHARED_RESOURCE; i++)
			{
				sharedResource[i] = rand() & 100;
			}
			/* Give up the mutex for next conversion. */
			xSemaphoreGive(mutexSem);
		}
		vTaskDelay(pdMS_TO_TICKS(1000));	/* delay in ms */
	}
	vTaskDelete(NULL);
}

void resourceTask2(void *pvParams)
{
	int i;
	BaseType_t res;

	for (;;)
	{
		/* Read the shared resource. */
		res = xSemaphoreTake(mutexSem, portMAX_DELAY);
		if (res == pdTRUE)
		{
			for (i = 0; i < SHARED_RESOURCE; i++)
			{
				printLog("%d", sharedResource[i]);
			}
			/* Give up the mutex for next conversion. */
			xSemaphoreGive(mutexSem);
		}
		vTaskDelay(pdMS_TO_TICKS(1000));	/* delay in ms */
	}
	vTaskDelete(NULL);
}
