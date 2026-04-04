/**
 * Peripheral configurations
 */

#include "main.h"

RCC_OscInitTypeDef iosc = {0};
RCC_ClkInitTypeDef iclk = {0};
GPIO_InitTypeDef igpio = {0};
UART_HandleTypeDef debugPort = {0};

void configOscClk(void)
{
	iosc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
   iosc.HSIState = RCC_HSI_ON;
   iosc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
   iosc.PLL.PLLState = RCC_PLL_NONE;
   HAL_RCC_OscConfig(&iosc);

   iclk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | 
						  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
   iclk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
   iclk.AHBCLKDivider = RCC_SYSCLK_DIV1;
   iclk.APB1CLKDivider = RCC_HCLK_DIV1;
   iclk.APB2CLKDivider = RCC_HCLK_DIV1;
   HAL_RCC_ClockConfig(&iclk, FLASH_LATENCY_0);
}

void configDebugPort(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_UART4_CLK_ENABLE();

	igpio.Mode = GPIO_MODE_AF_PP;
   igpio.Alternate = GPIO_AF8_UART4;  // UART4 uses AF8
   igpio.Pull = GPIO_NOPULL;
   igpio.Speed = GPIO_SPEED_FREQ_LOW;
   igpio.Pin = GPIO_PIN_10 | GPIO_PIN_11;  // PC10 and PC11
   HAL_GPIO_Init(GPIOC, &igpio);

	debugPort.Instance = UART4;
	debugPort.Init.BaudRate = 115200;
	debugPort.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	debugPort.Init.Mode = UART_MODE_TX;
	debugPort.Init.OverSampling = UART_OVERSAMPLING_16;
	debugPort.Init.Parity = UART_PARITY_NONE;
	debugPort.Init.StopBits = UART_STOPBITS_1;
	debugPort.Init.WordLength = UART_WORDLENGTH_8B;
	HAL_UART_Init(&debugPort);
}
 