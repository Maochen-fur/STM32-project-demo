/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FIRE1_Pin GPIO_PIN_1
#define FIRE1_GPIO_Port GPIOA
#define FIRE2_Pin GPIO_PIN_2
#define FIRE2_GPIO_Port GPIOA
#define FIRE3_Pin GPIO_PIN_3
#define FIRE3_GPIO_Port GPIOA
#define FIRE4_Pin GPIO_PIN_4
#define FIRE4_GPIO_Port GPIOA
#define MQ2_Pin GPIO_PIN_5
#define MQ2_GPIO_Port GPIOA
#define DHT11_Pin GPIO_PIN_6
#define DHT11_GPIO_Port GPIOA
#define FO_Pin GPIO_PIN_8
#define FO_GPIO_Port GPIOE
#define LEDB_Pin GPIO_PIN_10
#define LEDB_GPIO_Port GPIOE
#define LEDG_Pin GPIO_PIN_12
#define LEDG_GPIO_Port GPIOE
#define WAY5_Pin GPIO_PIN_11
#define WAY5_GPIO_Port GPIOB
#define WAY4_Pin GPIO_PIN_12
#define WAY4_GPIO_Port GPIOB
#define WAY3_Pin GPIO_PIN_13
#define WAY3_GPIO_Port GPIOB
#define WAY2_Pin GPIO_PIN_14
#define WAY2_GPIO_Port GPIOB
#define WAY1_Pin GPIO_PIN_15
#define WAY1_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_8
#define AIN1_GPIO_Port GPIOD
#define BIN1_Pin GPIO_PIN_9
#define BIN1_GPIO_Port GPIOD
#define AIN2_Pin GPIO_PIN_10
#define AIN2_GPIO_Port GPIOD
#define BIN2_Pin GPIO_PIN_11
#define BIN2_GPIO_Port GPIOD
#define PWMA_Pin GPIO_PIN_12
#define PWMA_GPIO_Port GPIOD
#define PWMB_Pin GPIO_PIN_13
#define PWMB_GPIO_Port GPIOD
#define SG90_Pin GPIO_PIN_14
#define SG90_GPIO_Port GPIOD
#define WATER_Pin GPIO_PIN_8
#define WATER_GPIO_Port GPIOA
#define TRIG_Pin GPIO_PIN_4
#define TRIG_GPIO_Port GPIOB
#define ECHO_Pin GPIO_PIN_5
#define ECHO_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_6
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_7
#define OLED_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
