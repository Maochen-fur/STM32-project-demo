#ifndef __TB6621_H
#define __TB6621_H			 

#include "main.h"
#include "tim.h"

#define	AIN1_H	HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET)
#define	AIN1_L	HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET)

#define	AIN2_H	HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET)
#define	AIN2_L	HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET)

#define	BIN1_H	HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET)
#define	BIN1_L	HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET)

#define	BIN2_H	HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET)
#define	BIN2_L	HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET)

void TB6621_Int(void);
void TB6621_A(uint8_t direction, int pwm_val);
void TB6621_B(uint8_t direction, int pwm_val);
void Read_Way_Int(void);
uint8_t move_to_fire(uint8_t mod);
#endif

