#ifndef __HC05BLE_H
#define __HC05BLE_H 			   
#include "main.h"
#include "usart.h"
#include "dma.h"
#include "oled_hard_i2c.h"

extern DMA_HandleTypeDef hdma_uart4_rx;
extern UART_HandleTypeDef huart4;
extern uint8_t ble_buff[255];

void MY_UART_IRQHandler_BLE(void);


extern char dir_cmd; // 方向指令 '1'-'9'
extern char spd_cmd; // 速度指令 'A'-'E'
extern int speed;


uint8_t Mode_Check(uint8_t mod);

uint8_t BLE_MOD(uint8_t mod);




#endif
