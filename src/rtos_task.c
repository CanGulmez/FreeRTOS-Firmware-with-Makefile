/**
 * FreeRTOS Task Management
 * 
 * Tasks are implemented as C functions and must be implemented
 * as expected function prototype:
 * 
 * 	void vATaskFunction(void *pvParameters);
 * 
 * Each task is a small program in its own right. It has an entry
 * point, will normally run forever in an infinite loop, and does
 * not exit.
 * 
 * An application may consist of many tasks. If the processor
 * running the application including a single core, then only one
 * task may be executing at any given time. This implies that a
 * task may exist i one of two states: Running and Not Running.
 * 
 * Each task requires two blocks of RAM: one to hold its Task
 * Control Block (TCB) and one to store its stack.
 * 
 * 	BaseType_t xTaskCreate(TaskFunction_t pvTaskCode,
 * 								  const char * const pcName,
 * 								  configSTACK_DEPTH_TYPE usStackDepth,
 * 								  void * pvParameters,
 * 								  UBaseType_t uxPriority,
 * 								  TaskHandle_t * pxCreatedTask);
 * 
 * The FreeRTOS scheduler always ensures the highest priority task
 * that can run is the task selected to enter the Running state.
 * Tasks of eqaul priority are transitioned into and out of the
 * Running state in turn.
 * 
 * The scheduler executes at the end of each time slice to select
 * the next task to run. A periodic interrupt, called the 'tick'
 * 'interrupt', is used for this purpose. The configTICK_RATE_HZ
 * compile-time configuration constant sets the frequency of the
 * tick interrupt, and so also the length of each time slice. For
 * example, setting configTICK_RATE_HZ to 100 results in each
 * time slice lasting 10 ms. The time between two tick interrupts
 * is called the 'tick period' - so one time slice equals one 
 * tick period.
 * 
 * Using pdMS_TO_TICKS() to specify times in ms, rather than
 * directly as ticks, ensures times specified within the 
 * application do not change if the tick frequency is changed.
 * 
 * The parameters to vTaskDelayUntil() specify, instead, the
 * exact tick count value at which the calling task should be
 * removed from Blocked state into the Ready state. 
 * vTaskDelayUntil() is the API function to use when a fixed
 * execution period is required (where you want your task to
 * execute periodically with a fixed frequency).
 * 
 * 	void vTaskDelayUntil(TickType_t * pxPreviousWakeTime,
 * 								TickType_t xTimeIncrement);
 * 
 * There must always be at least one task that can enter the
 * Running state. To ensure this is the case, the scheduler
 * automatically creates an Idle task when vTaskStartScheduler()
 * is called. This idle task does very little more than sit in
 * a loop. The idle task has the lowest possible priority (0),
 * to ensure it never prevents a higher priority application task
 * from entering the Running state.
 * 
 * An idle task hook function must never attempt to block or
 * suspend itself.
 * 
 * 	viod vApplicationIdleHook(void);
 * 
 * configUSE_IDLE_HOOK must be set to 1 in FreeRTOSConfig.h for
 * the idle hook function to get called.
 * 
 * Other useful functions:
 * 
 * 	void vTaskPrioritySet(TaskHandle_t xTask, 
 * 								 UBaseType_t uxNewPriority);
 * 	UBaseType_t uxTaskPriorityGet(TaskHandle_t xTask);
 * 
 * The scheduling algorithm is the software routine that decides
 * which Ready state task to transition into the Running state.
 * 
 * 	Algorithm	configUSE_PREEMPTION		configUSE_TIME_SLICING
 * 	---------	--------------------		----------------------
 * 	Preemptive				1								1 
 * 		With
 *	  Time Slicing
 *
 * 	Preemptive				1								0
 * 	 Without
 *   Time Slicing
 * 
 *   Co-Operative				0							  Any
 * 
 * Time slicing is used to share processing time between tasks of
 * equal priority, even when the tasks do not explicitly yield or
 * enter the Blocked state. A time slice is eqaul to the time
 * between two RTOS tick interrupts.
 */

#include "main.h"

void simpleTask1(void *pvParams)
{
	int32_t localVar = 0;

	for (;;)
	{
		printLog("simple task 1: %ld", localVar++);

		vTaskDelay(pdMS_TO_TICKS(2000));	/* delay in ms */
	}
	vTaskDelete(NULL);
}

void simpleTask2(void *pvParams)
{
	int32_t localVar = 0;

	for (;;)
	{
		printLog("simple task 2: %ld", localVar++);
		
		vTaskDelay(pdMS_TO_TICKS(6000));	/* delay in ms */
	}
	vTaskDelete(NULL);
}

void simpleTask3(void *pvParams)
{
	int32_t localVar = 0;
	TickType_t lastWake;

	/**
	 * The lastWake variable needs to be initialized with the
	 * current tick count. Note that this is the only time the
	 * variable is written to explicitly. After this lastWake
	 * is automatically updated within vTaskDelayUntil().
	 */
	lastWake = xTaskGetTickCount();

	for (;;)
	{
		printLog("simple task 3: %ld (tick count: %ld)", 
					localVar++, lastWake);
		
		vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(5000));
	}
	vTaskDelete(NULL);
}

void simpleTask4(void *pvParams)
{
	int32_t localVar = 0;
	UBaseType_t taskPriority;

	/**
	 * Set the calling task priority to maximum priority.
	 */
	vTaskPrioritySet(NULL, (configMAX_PRIORITIES - 1));

	for (;;)
	{
		/**
		 * Get the calling task priority.
		 */
		taskPriority = uxTaskPriorityGet(NULL);

		printLog("simple task 4: %ld (task priority: %ld)", 
					localVar++, taskPriority);

		vTaskDelay(pdMS_TO_TICKS(3000));	/* delay in ms */
	}
	vTaskDelete(NULL);
}
