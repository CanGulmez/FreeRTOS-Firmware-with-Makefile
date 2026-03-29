/**
 * FreeRTOS Event Groups Management
 * 
 * Event groups are another feature of FreeRTOS that allow events
 * to be communicated to tasks. Unlike queues and semaphores:
 * 
 * + Event groups allow a task to wait in the Blocked state for a
 *   combination of one of more events to occur.
 * + Event groups unblock all the tasks that were waiting for the
 *   same event, or comination of events, when the event occurs.
 * 
 * These unique properties of event groups make them useful for
 * synchronizing multiple tasks, broadcasting events to more than
 * one task, allowing a task to wait in the Blocked stte for any
 * one of a set of events to occur.
 * 
 * An event flag is a boolean value used to indicate if an event
 * has occured or not. An event group is a set of event flags.
 * 
 * 	EventGroupHandle_t xEventGroupCreate(void);
 * 	EventBits_t xEventGroupSetBits(EventGroupHandle_t xEventGroup,
 * 											 const EventBits_t uxBitsToSet);
 * 	EventBits_t xEventGroupWaitBits(EventGroupHandle_t xEventGroup,
 * 											  const EventBits_t uxBitsToWaitFor,
 * 											  const BaseType_t xClearOnExit,
 * 											  const BaseType_t xWaitForAllBits,
 * 											  TickType_t xTicksToWait);
 * 
 * The xEventGroupWaitBits() API function allows a task to read
 * the value of an event group, and optionally wait in the Blocked
 * state for one or more event bits in the event group to become
 * set, if the event bits are not already set.
 */

#include "main.h"

