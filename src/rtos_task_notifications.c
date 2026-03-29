/**
 * FreeRTOS Task Notifications
 * 
 * FreeRTOS applications are typically structured as a series 
 * of independent tasks that communicate with each other to 
 * provide the system functionality. Task notifications are an
 * efficient mechanism allowing one task to directly notify
 * another task.
 * 
 * Task notifications allow tasks to interact with other tasks,
 * and to synchronize with ISRs, without the need for a separate
 * communication object.
 * 
 * This wide range of usage scenarios can be achieved by using
 * the xTaskNotify() API to send a task notification, and the
 * xTaskNotifyWait() API function to receive a task notification.
 * 
 * 	BaseType_t xTaskNotifyGive(TaskHandle_t xTaskToNotify);
 * 	uint32_t ulTaskNotifyTake(BaseType_t xClearCountOnExit,
 * 									  TickType_t xTicksToWait);
 */

#include "main.h"
