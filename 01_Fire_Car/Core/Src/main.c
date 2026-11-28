/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay.h"
#include "dht11.h"
#include "oled_hard_i2c.h"
#include "get_ao.h"
#include "esp01s.h"
#include "hcsr04.h"
#include "sg90.h"
#include "tb6621.h"
#include "hc05ble.h"

uint8_t mod = 0;		// 0：自动循迹 1：蓝牙控制
uint8_t fire_way = 0;	
uint8_t fire_lever = 0;	
uint8_t hex = 0;
uint8_t BLEM = 1;

DHT11_Data_TypeDef DHT11_Data;

uint32_t wendu=20;
uint32_t shidu=10;
uint32_t num = 0;
uint16_t distance = 400 ;

uint32_t next_mq2_time = 0;   // 记录 MQ2 下次该发送的时刻
uint32_t next_dht_time = 0;   // 记录 DHT11 下次该发送的时刻
uint32_t next_sr04_time = 0; // 下一次触发超声波的时间
uint8_t upload_counter = 0;  // 超声波上传计数器

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_UART4_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	delay_s(5);
	OLED_Init();
	SG90_Int();
	TB6621_Int();
	
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);	 
	HAL_UART_Receive_DMA(&huart1, (uint8_t*)wifi_buff, 255);
	
	__HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);	 
	HAL_UART_Receive_DMA(&huart4, (uint8_t*)ble_buff, 255);
	
	ESPO1S_Int();
	ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=0\r\n" );
	delay_ms(100);
	ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=Lever&msg=0\r\n" );
	
	uint32_t now = HAL_GetTick();
  //
  // MQ2: 现在 + 2500ms = 第一次发送时间 (2.5秒后)
  next_mq2_time = now + 2500; 
  
  // DHT11: 现在 + 5000ms = 第一次发送时间 (5.0秒后)
  next_dht_time = now + 5000; 

	
	//TB6621_A(1,15000); 
	//TB6621_B(1,15000);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		
		get_adc_vaule();	//获得所以ADC值
//		OLED_Show_ADC_Value();	//展示所有ADC值
		
		 // ---  DHT11 (每5秒一次，起始偏移5.0秒) ---
    if ((int32_t)(HAL_GetTick() - next_dht_time) >= 0 )
    {
        // 1. 更新下一次的时间点
        next_dht_time += 5000;
				if (DHT11_ReadData(&DHT11_Data) == 1) // 只有读取成功才更新
				{
						shidu = (uint32_t)(DHT11_Data.humi_int);
						wendu = (uint32_t)(DHT11_Data.temp_int);			
						ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=DHT11&msg=#%d#%d\r\n",wendu,shidu);
						if ((wendu > 38 || shidu > 90 )&& mod != 5)
						{
								mod = 4;
						}
					
				}
			}

			
		if ((int32_t)(HAL_GetTick() - next_mq2_time) >= 0)
		{
			next_mq2_time += 5000; 
			ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MQ2&msg=%d\r\n", (uint32_t)adc_value[4] );
			if (adc_value[4] > 3800)
			{
					mod = 5;
			}
			
		}
		
		
		
		
		mod = Mode_Check(mod) ;
//		OLED_ShowNum(30,8,mod,1,8,1);
//		OLED_ShowNum(37,8,fire_lever,1,8,1);
//		OLED_ShowNum(30,0,(hex++)%100,2,8,1);
//		OLED_Refresh();	//OLED显示函数
		

			
		
		if (mod == 0)	//自动循迹模式
		{
			HAL_GPIO_WritePin (LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LEDG_GPIO_Port,LEDG_Pin,GPIO_PIN_SET);
			fire_way = check_fire_min();	//读取火焰传感器值，返回 低于3000 的 火焰传感器编号（1~4），无则返回 0 .
			
			if (fire_way != 0)
				{
					//连续读取5次，判断是不是同一路发现了火情
					for(uint16_t  i=0;i<5;i++) 
						{
							get_adc_vaule();
							if(check_fire_min() != fire_way )	//如果误判
							{
								fire_way = 0 ;	//回到自动循迹状态
								break ; //跳出for循环
							}
							delay_ms(2);
						}
					
					if (fire_way != 0) 	//经过5次判断后，仍然发现火焰
						{
							fire_lever=1;		//表示发现火情
											
//							OLED_ShowNum(46,8,fire_lever,1,8,1);
							
							fire_lever = move_to_fire(fire_way);	//瞄准并灭火函数
							
							if(fire_lever == 2) 	//灭火成功
								{
									mod = 3;
								}
							
							if(fire_lever == 3)		//灭火失败	
								{
									mod = 3;
								}
							if(fire_lever == 5) //丢失火源
								{
									mod = 3;
								}
						}
				}
				
			else
				
				{
					 if (HAL_GetTick() >= next_sr04_time) 
							{
									next_sr04_time = HAL_GetTick() + 200; // 设置下次时间：200ms 后
									
									   // --- 上传逻辑 ---
									upload_counter++; // 计数器 +1
									// 比如：每 10 次测距，上传一次数据
									distance = SR04_Get_Distance();
									if(distance<110)
									{
										
										ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=2\r\n" );
										mod = 2 ;
									}
//									OLED_ShowNum(44,0,distance,3,8,1);
									if (upload_counter >= 10) 
									{
											upload_counter = 0; // 计数器清零
											ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=SR04&msg=%d\r\n", distance);
									}
								
							}
						Read_Way_Int();	//五路循迹
				}
			
		}
		
		
		else if (mod == 1)
		{
			HAL_GPIO_WritePin (LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin (LEDG_GPIO_Port,LEDG_Pin,GPIO_PIN_RESET);
			if(BLEM == 1)
			{
				ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=1\r\n" );
				 BLEM = 0;
			}
			
			mod = BLE_MOD(mod);
			
			if(mod == 0)
			{
				ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=0\r\n" );
				ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=Lever&msg=0\r\n" );
				BLEM = 1;
			}


			
		}
		
		else if (mod == 3)
		{			

			TB6621_A(0,10000);
			TB6621_B(0,10000);
			HAL_GPIO_WritePin (FO_GPIO_Port,FO_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin (LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin (LEDG_GPIO_Port,LEDG_Pin,GPIO_PIN_RESET);
			delay_ms(150);
			HAL_GPIO_WritePin (FO_GPIO_Port,FO_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_RESET);

			delay_ms(150);			
			
		}
		else if (mod == 2)	//遇到障碍
		{
			TB6621_A(0,10000);
			TB6621_B(0,10000);
			HAL_GPIO_WritePin (FO_GPIO_Port,FO_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin (LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin (LEDG_GPIO_Port,LEDG_Pin,GPIO_PIN_RESET);
			delay_ms(500);
			HAL_GPIO_WritePin (FO_GPIO_Port,FO_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_RESET);
			delay_ms(500);			
			distance = SR04_Get_Distance();
			ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=SR04&msg=%d\r\n", distance);
			if	(distance > 110)
			{
				ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=0\r\n" );
				mod = 0;
				
			}
		}
		else if (mod == 4) //温湿度超标
		{			
			

			TB6621_A(0,10000);
			TB6621_B(0,10000);
			HAL_GPIO_WritePin (FO_GPIO_Port,FO_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin (LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin (LEDG_GPIO_Port,LEDG_Pin,GPIO_PIN_RESET);
			delay_ms(150);
			HAL_GPIO_WritePin (FO_GPIO_Port,FO_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_RESET);
			delay_ms(750);			
		  if (DHT11_ReadData(&DHT11_Data) == 1)
			{
					shidu = (uint32_t)(DHT11_Data.humi_int);
					wendu = (uint32_t)(DHT11_Data.temp_int);
					
					// 发送温湿度信息到云平台
					ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=DHT11&msg=#%d#%d\r\n", wendu, shidu);
					ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=4\r\n" );
					// 检查是否低于阈值（注意：使用<还是<=根据需求）
					if (wendu <= 38 && shidu <= 90 )
					{
							mod = 0;  // 恢复正常模式
						 ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=0\r\n" );
					}
					
			}
			
		}
		else if (mod == 5)//烟雾浓度超标
		{			

			TB6621_A(0,10000);
			TB6621_B(0,10000);
			HAL_GPIO_WritePin (FO_GPIO_Port,FO_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin (LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin (LEDG_GPIO_Port,LEDG_Pin,GPIO_PIN_RESET);
			delay_ms(150);
			HAL_GPIO_WritePin (FO_GPIO_Port,FO_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (LEDB_GPIO_Port,LEDB_Pin,GPIO_PIN_RESET);
			delay_ms(750);	
			
			//get_adc_vaule();
			ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MQ2&msg=%d\r\n", (uint32_t)adc_value[4] );
			ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=5\r\n" );
			if (adc_value[4] < 3800)
			{
					mod = 0;
				ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=0\r\n" );
			}			
		}
			
			


		

		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
