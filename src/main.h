/**
 * Complete FreeRTOS Tutorial
 */

/* Libraries */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/stat.h>

#include "stm32f4xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include "event_groups.h"

/* GLobal definitions */

#define BUF_SIZE				128

#define FILE					__FILE__
#define LINE					__LINE__

#define STATUS(status) 		((status == HAL_ERROR) 		? "ERROR" 	: 			\
									 (status == HAL_BUSY) 		? "BUSY"		:			\
									 (status == HAL_TIMEOUT) 	? "TIMEOUT" :			\
													 					  "UNDEFINED")

#define SHARED_RESOURCE		3

/*****************************************************************************/
/*****************************************************************************/

typedef enum
{
	eSender1,
	eSender2
} DataSource_t;

typedef struct
{
	uint8_t pValue;
	DataSource_t eDataSource;
} Data_t;

extern int sharedResource[SHARED_RESOURCE];

extern RCC_OscInitTypeDef iosc;
extern RCC_ClkInitTypeDef iclk;
extern GPIO_InitTypeDef igpio;
extern UART_HandleTypeDef debugPort;

extern QueueHandle_t queue;
extern TimerHandle_t autoReloadTimer;
extern TimerHandle_t oneShotTimer;
extern SemaphoreHandle_t binarySem;
extern SemaphoreHandle_t mutexSem;

/*****************************************************************************/
/*****************************************************************************/

/**
 * Transmit the logs from MCU to PC over serial UAR line.
 */
#define printLog(format, ...)																\
do {																								\
	char buffer[BUF_SIZE];																	\
																									\
	snprintf(buffer, BUF_SIZE, format "\r\n", ##__VA_ARGS__);					\
	HAL_UART_Transmit(&debugPort, (uint8_t*) buffer, strlen(buffer),			\
							HAL_MAX_DELAY);													\
} while (0)

/**
 * Transmit the error from MCU to PC over serial UAR line.
 */
#define printError(status, format, ...)												\
do {																								\
	char buffer[BUF_SIZE];																	\
																									\
	snprintf(buffer, BUF_SIZE, "*** " format 	" (STATUS = %s) " 				\
		"(%s::%d) ***\r\n", ##__VA_ARGS__, STATUS(status), FILE, LINE);		\
	HAL_UART_Transmit(&debugPort, (uint8_t*) buffer, sizeof(buffer),			\
		HAL_MAX_DELAY);																		\
} while (0)

/**
 * Transmit the kernel message from MCU to PC over serial UAR line.
 */
#define printKernel(format, ...)															\
do {																								\
	char buffer[BUF_SIZE];																	\
																									\
	snprintf(buffer, BUF_SIZE, "*** " format 	" (%s::%d) ***\r\n", 			\
		##__VA_ARGS__, FILE, LINE);														\
	HAL_UART_Transmit(&debugPort, (uint8_t*) buffer, sizeof(buffer),			\
		HAL_MAX_DELAY);																		\
} while (0)

/*****************************************************************************/
/*****************************************************************************/

/* Function prototypes */

extern int _read(int, char *, int);
extern int _write(int, char *, int);
extern int _lseek(int, int, int);
extern int _close(int);
extern int _getpid(void);
extern int _kill(int);
extern int _fstat(int, struct stat *);
extern int _isatty(int);

extern void configOscClk(void);
extern void configDebugPort(void);

extern void simpleTask1(void *);
extern void simpleTask2(void *);
extern void simpleTask3(void *);
extern void simpleTask4(void *);

extern void senderTask(void *);
extern void receiverTask(void *);

extern void autoReloadTimerCallback(TimerHandle_t);
extern void oneShotTimerCallback(TimerHandle_t);

extern void syncTask1(void *);
extern void syncTask2(void *);

extern void resourceTask1(void *);
extern void resourceTask2(void *);

extern void SysTick_Handler(void);
extern void xPortSysTickHandler(void);
extern void vApplicationIdleHook(void);
