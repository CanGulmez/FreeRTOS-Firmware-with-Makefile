/**
 * Interrupt Service Routine (IRQ) Handlers
 */

#include "main.h"

void SysTick_Handler(void) 
{
   HAL_IncTick();
	
	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) 
	{
		xPortSysTickHandler();
	}
}

void EXTI0_IRQHandler(void)
{
	BaseType_t res, taskWoken;

	printLog("EXTI0_IRQHandler() started here...");

	taskWoken = pdFALSE;

	res = xSemaphoreGiveFromISR(binarySem, &taskWoken);
	if (res != pdPASS)
		printKernel("semaphore cannot be given from EXTI0_IRQHandler()!");

	portYIELD_FROM_ISR(taskWoken);	
}
