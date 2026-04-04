/**
 * FreeRTOS Low Power Support
 * 
 * FreeRTOS offers an easy way to tap into low power modes with
 * the IDLE task hooks and tickless idle mode.
 * 
 * It is common to reduce the power consumed by the 
 * microcontroller on which FreeRTOS is running by using the IDLE 
 * task hook to place the microcontroller into a low power state.
 * 
 * The built-in tickless idle functionality is enabled by defining
 * configUSE_TICKLESS_IDLE as 1 in FreeRTOSConfig.h.
 */

#include "main.h"

void vApplicationIdleHook(void)
{
	__WFI();		/* enter into the deep sleep mode */
}
