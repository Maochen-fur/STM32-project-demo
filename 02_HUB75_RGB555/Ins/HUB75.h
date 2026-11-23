#ifndef __HUB75_H
#define __HUB75_H

#include "stm32f10x.h"
#include "gpio.h"
#include "delay.h"
#include <stdio.h>


//// 初始化 HUB75 接口
//void HUB75_Init(void);

//// 发送一行数据到 LED 屏幕
//void HUB75_SendData(uint8_t* data, uint8_t row);

//// 刷新屏幕
//void HUB75_RefreshScreen(void);
typedef struct 
{
	uint16_t B:5;
	uint16_t G:5;
	uint16_t R:5;	
	uint16_t null:1;		
}led_data;

extern led_data *img_data;
extern uint16_t *gram_rgb_555 ;

void RedDis(uint8_t r);
void BlueDis(uint8_t b);
void GreenDis(uint8_t g);
void led_DRamDis(uint16_t *pdata);

void HUB75_RefreshScreen(void);



//extern unsigned char gImage_rgb[4096];


#endif
