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
 * 
 * Often it is necessary to use the functionality provided by a
 * Freertos API function from an interrupt service routine (ISR).
 * FreeRTOS serves the functions ending with "FromISR" for this.
 * 
 * There are several reasons why context switches do not occur
 * automatically inside the interrupt safe version of an API
 * function:
 * 
 * + Avoiding unnecessary context switches
 * + Control over the execution sequence
 * + Execution in the RTOS tick interrupt
 */

#include "main.h"

void rtosTask9(void *pvParams)
{
	static int i = 0;
	BaseType_t res;

	printLog("rtosTask9() started here...");

	for (;;)
	{	
		res = xSemaphoreTake(binarySem, portMAX_DELAY);
		if (res != pdPASS)
			printKernel("semaphore cannot be taken from rtosTask9()!");

		printLog("doing the rtosTask9() stuffs (%d)...", ++i);
	}
	vTaskDelete(NULL);
}

void rtosTask10(void *pvParams)
{
	printLog("rtosTask10() started here...");

	/* Enable the EXTI0 interrupt. */
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	HAL_NVIC_SetPriority(EXTI0_IRQn, 6, 0);

	for (;;)
	{
		vTaskDelay(pdMS_TO_TICKS(2000));	/* delay in ms */

		printLog("EXTI0 interrupt is triggered from rtosTask10().");

		/* Trigger the EXTI0 interrupt handler. */
		HAL_NVIC_SetPendingIRQ(EXTI0_IRQn);
			
		vTaskDelay(pdMS_TO_TICKS(1000));	/* delay in ms */
	}
	vTaskDelete(NULL);
}
