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
