#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

#define DATA_PORT GPIOA
#define ADDR_PORT GPIOB
#define CTRL_PORT GPIOB

//GPIOA
#define R1_PIN GPIO_Pin_0
#define G1_PIN GPIO_Pin_1
#define B1_PIN GPIO_Pin_2
#define R2_PIN GPIO_Pin_3
#define G2_PIN GPIO_Pin_4
#define B2_PIN GPIO_Pin_5

//GPIOB
#define A_PIN GPIO_Pin_0
#define B_PIN GPIO_Pin_1
#define C_PIN GPIO_Pin_10
#define D_PIN GPIO_Pin_11

//GPIOB
#define CLK_PIN GPIO_Pin_6
#define LAT_PIN GPIO_Pin_7
#define OE_PIN GPIO_Pin_8


// 定义高电平和低电平的宏

#define R1_H   GPIO_SetBits(DATA_PORT, R1_PIN)
#define R2_H   GPIO_SetBits(DATA_PORT, R2_PIN)
#define G1_H   GPIO_SetBits(DATA_PORT, G1_PIN)
#define G2_H   GPIO_SetBits(DATA_PORT, G2_PIN)
#define B1_H   GPIO_SetBits(DATA_PORT, B1_PIN)
#define B2_H   GPIO_SetBits(DATA_PORT, B2_PIN)
#define A_H    GPIO_SetBits(ADDR_PORT, A_PIN)
#define B_H    GPIO_SetBits(ADDR_PORT, B_PIN)
#define C_H    GPIO_SetBits(ADDR_PORT, C_PIN)
#define D_H    GPIO_SetBits(ADDR_PORT, D_PIN)
#define CLK_H  GPIO_SetBits(CTRL_PORT, CLK_PIN)
#define LAT_H  GPIO_SetBits(CTRL_PORT, LAT_PIN)
#define OE_H   GPIO_SetBits(CTRL_PORT, OE_PIN)


#define R1_L   GPIO_ResetBits(DATA_PORT, R1_PIN)
#define R2_L   GPIO_ResetBits(DATA_PORT, R2_PIN)
#define G1_L   GPIO_ResetBits(DATA_PORT, G1_PIN)
#define G2_L   GPIO_ResetBits(DATA_PORT, G2_PIN)
#define B1_L   GPIO_ResetBits(DATA_PORT, B1_PIN)
#define B2_L   GPIO_ResetBits(DATA_PORT, B2_PIN)
#define A_L    GPIO_ResetBits(ADDR_PORT, A_PIN)
#define B_L    GPIO_ResetBits(ADDR_PORT, B_PIN)
#define C_L    GPIO_ResetBits(ADDR_PORT, C_PIN)
#define D_L    GPIO_ResetBits(ADDR_PORT, D_PIN)
#define CLK_L  GPIO_ResetBits(CTRL_PORT, CLK_PIN)
#define LAT_L  GPIO_ResetBits(CTRL_PORT, LAT_PIN)
#define OE_L   GPIO_ResetBits(CTRL_PORT, OE_PIN)




void GPIO_Config(void);


#endif
