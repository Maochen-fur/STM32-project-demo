#ifndef __ESP01S_H_
#define __ESP01S_H_

#include "main.h"
#include <stdarg.h> 
#include <string.h>
#include <stdio.h>
#include "oled_hard_i2c.h"

extern DMA_HandleTypeDef hdma_usart1_rx;
extern UART_HandleTypeDef huart1;
extern uint8_t wifi_buff[255];

void MY_UART_IRQHandler_WIFI(void);
void 	ESPO1S_Int(void);

FlagStatus ESP01S_SendCmd_Printf(char *res, char *fmt, ...);

#endif

