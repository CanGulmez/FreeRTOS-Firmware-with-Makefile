/**
 ******************************************************************************
 * @file 	it.c
 * @author 	Ahmet Can GULMEZ
 * @brief 	Interrupt Service Routine (IRQ) handlers.
 * 
 ******************************************************************************
 * @attention
 * 
 * Copyright (c) 2025 Ahmet Can GULMEZ.
 * All rights reserved.
 * 
 * This software is licensed under the MIT License.
 * 
 ******************************************************************************
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
