/**
 * FreeRTOS Hook Functions
 * 
 * Idle hook: The idle task run here. It is created automatically.
 * 
 * There are two ways to detect the stack overflow:
 * + Checking the stack pointer at context switch, minimal, fast,
 *   used with configCHECK_FOR_STACK_OVERFLOW = 1.
 * + Writing a known canary value at the stack boundary and checks
 *   if it's been overwritten, slighly more overhead, used with
 *   configCHECK_FOR_STACK_OVERFLOW = 2.
 */

#include "main.h"

void vApplicationIdleHook(void)
{
	__WFI();			/* enter into the deep sleep! */
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, const char *pcTaskName)
{
	printKernel("detected the stack overflow at '%s'!", pcTaskName);

	/* Trap here. Use the debugger to inspect from here... */
	for (;;);
}
