/*
 * SysConfig Configuration Steps:
 *   GPIO:
 *     1. Add a GPIO module.
 *     2. Name the group as "GPIO_OLED".
 *     3. Name the pins as "OLED_SCL" and "OLED_SDA".
 *     4. Set the pins according to your needs.
 */

#ifndef __OLED_SOFTWARE_I2C_H
#define __OLED_SOFTWARE_I2C_H

#include "main.h"

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据




//----------------------------------------------------------------------------------
//OLED SSD1306 I2C 时钟SCL
//#define		OLED_SCL_Set()			  (HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin,GPIO_PIN_SET))
//#define		OLED_SCL_Clr()				(HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin,GPIO_PIN_RESET))

//----------------------------------------------------------------------------------
//OLED SSD1306 I2C 数据SDA
//#define		OLED_SDA_Set()				(HAL_GPIO_WritePin(OLED_SDA_GPIO_Port, OLED_SDA_Pin,GPIO_PIN_SET))
//#define		OLED_SDA_Clr()			  (HAL_GPIO_WritePin(OLED_SDA_GPIO_Port, OLED_SDA_Pin,GPIO_PIN_RESET))
				   

//OLED控制用函数
void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void OLED_Set_Pos(uint8_t x, uint8_t y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t sizey);
uint32_t oled_pow(uint8_t m,uint8_t n);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t sizey);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t sizey);
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t no,uint8_t sizey);
void OLED_DrawBMP(uint8_t x,uint8_t y,uint8_t sizex, uint8_t sizey,uint8_t BMP[]);
void OLED_Init(void);

void OLED_SCL_Set(void);
void OLED_SCL_Clr(void);
void OLED_SDA_Set(void);
void OLED_SDA_Clr(void);

#endif /* #ifndef __OLED_SOFTWARE_I2C_H */
