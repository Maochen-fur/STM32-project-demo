#include "tb6621.h"
#include "get_ao.h"
#include "delay.h"
#include "esp01s.h"


void TB6621_Int(void)
{
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	AIN1_L;
	AIN2_L;
	BIN1_L;
	BIN2_L;
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,0);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,0);
	
}



/**
 * @brief  循迹逻辑读取与控制函数
 * @note   根据5路循迹传感器的状态，执行不同的转向策略并调整左右电机速度。
 *         传感器布局：WAY1(最左) ... WAY3(中) ... WAY5(最右)
 */
            
	void Read_Way_Int(void)
	{
		if (HAL_GPIO_ReadPin(WAY1_GPIO_Port, WAY1_Pin) == GPIO_PIN_SET)
		{
			TB6621_A(2,14000);
			TB6621_B(1,14000);
		}
		else if (HAL_GPIO_ReadPin(WAY5_GPIO_Port, WAY5_Pin) == GPIO_PIN_SET)
		{
			TB6621_A(1,14000);
			TB6621_B(2,14000);
		}
		else if (HAL_GPIO_ReadPin(WAY2_GPIO_Port, WAY2_Pin) == GPIO_PIN_SET)
		{
			TB6621_A(1,7000);
			TB6621_B(1,14000);
		}
		else if (HAL_GPIO_ReadPin(WAY4_GPIO_Port, WAY4_Pin) == GPIO_PIN_SET)
		{
			TB6621_A(1,14000);
			TB6621_B(1,6000);
		}
		else
		{
			TB6621_A(1,13000);
			TB6621_B(1,13000);
		}
	}



/**
 * @brief 控制小车移动以靠近火焰源
 * 
 * @param fire_way 目标火焰传感器的编号 (1-4)
 *        - 1: 左侧传感器检测到最强信号 -> 向左转/
 *        - 2: 左中传感器检测到最强信号 -> 微调/
 *        - 3: 右中传感器检测到最强信号 -> 微调/前进
 *        - 4: 右侧传感器检测到最强信号 -> 向右转/调整
 * 
 * @return uint8_t 
 *         - (目前无返回值): 进入死循环持续追踪，直到外部复位或断电
 */
uint8_t move_to_fire(uint8_t fire_way)
{	
	TB6621_A(0,10000);
	TB6621_B(0,10000);

	ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=Lever&msg=1\r\n");
	ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=3\r\n" );
	while(1)
	{
		get_adc_vaule();	//获取最新的ADC值
//		OLED_Show_ADC_Value();
		fire_way = check_fire_min();
		
		if(fire_way==1)		//左1火焰传感器检测到大左转
		{
		TB6621_A(2,13000);
		TB6621_B(1,13000);
		}
		else if(fire_way==4)		//右4火焰传感器检测到大右转
		{
		TB6621_A(1,13000);
		TB6621_B(2,13000);
		}
		else if(fire_way==2)	//左2火焰传感器检测到判断比值
		{
			if(( adc_value[1]-adc_value[2] ) < 1000 )		//2火焰传感器 和 3火焰传感器 值近似，停止，否则小左转
			{
				TB6621_A(0,10000);
				TB6621_B(0,10000);
				//开始灭火
				HAL_GPIO_WritePin(WATER_GPIO_Port, WATER_Pin, GPIO_PIN_SET);
				delay_s(3);
				HAL_GPIO_WritePin(WATER_GPIO_Port, WATER_Pin, GPIO_PIN_RESET);
				//ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=3\r\n" );
				//判断是否灭火，返回fire_lever的值
				uint8_t no_fire_count = 0;
				for(int k=0; k<20; k++) 
					{
						get_adc_vaule();
						if(check_fire_min() == 0) 
							{
								no_fire_count++;
							}
						delay_ms(5); // 采样间隔
					}

				// 分割线设为 16 (80%)
				if(no_fire_count >= 16) 
					{
						ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=Lever&msg=2\r\n");
						return 2; // 成功
					} 
				else 
					{
						ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=Lever&msg=3\r\n");
						return 3; // 失败
					}
			}
			else
			{
			TB6621_A(2,11000);
			TB6621_B(1,11000); 
			}
		}
		else if(fire_way==3)	//右3火焰传感器检测到判断比值
		{
			if(( adc_value[2]-adc_value[1] ) < 1000
				)		//3火焰传感器 和 2火焰传感器 值近似，停止，否则小右转
			{
				TB6621_A(0,10000);
				TB6621_B(0,10000);
				//开始灭火
				HAL_GPIO_WritePin(WATER_GPIO_Port, WATER_Pin, GPIO_PIN_SET);
				delay_s(3);
				HAL_GPIO_WritePin(WATER_GPIO_Port, WATER_Pin, GPIO_PIN_RESET);
		//		ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=MOD&msg=3\r\n" );
				//判断是否灭火，返回fire_lever的值
				uint8_t no_fire_count = 0;
				for(int k=0; k<20; k++) 
					{
						get_adc_vaule();
						if(check_fire_min() == 0) 
							{
								no_fire_count++;
							}
						delay_ms(5); // 采样间隔
					}

				// 分割线设为 16 (80%)
				if(no_fire_count >= 16) 
					{
						ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=Lever&msg=2\r\n");
						return 2; // 成功
					} 
				else 
					{
						ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=Lever&msg=3\r\n");
						return 3; // 失败
					}
			}
			else		
			{
			TB6621_A(1,11000);
			TB6621_B(2,11000);
			}
		}
		else	//火源丢失
		{
			uint16_t i = 0;
			
			for(i=0;i<1000;i++) 
				{
					get_adc_vaule();
					fire_way = check_fire_min();
					if( fire_way != 0 )		//重新发现火源
						{
							break ; //跳出for循环
						}
					delay_ms(10);
				}
				
			if(i >= 1000)
				{
					TB6621_A(0,10000);
					TB6621_B(0,10000);
					ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=Lever&msg=5\r\n");
					return 5;		//丢失火源
				}
		}
		
	}
}

	/**
	 * @brief  控制电机A (左电机) 的方向和速度
	 * @param  direction: 方向控制
	 *         0: 停止 (短刹/自由停，代码中实现为两脚置低)
	 *         1: 正转
	 *         2: 反转
	 * @param  pwm_val: PWM占空比值 (速度)，范围建议 0 - 20000 (需匹配定时器ARR值)
	 */
	void TB6621_A(uint8_t direction, int pwm_val)
	{
			// 限制PWM值在安全范围内
			if (pwm_val > 20000) pwm_val = 20000;
			if (pwm_val < 0)  pwm_val = 0;
			switch (direction)
			{
					case 0: // 停止 (短刹模式：两个输入都置高，电机快速制动)
							AIN1_L;
							AIN2_L;
							break;
					case 1: // 正转
							AIN1_H;
							AIN2_L;
							break;
					case 2: // 反转
							AIN1_L;
							AIN2_H;
							break;
					default: // 错误输入，默认停止
							AIN1_H;
							AIN2_H;
							pwm_val = 0 ;
							break;
			}
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, pwm_val);
	}



/**
 * @brief  控制电机B (右电机) 的方向和速度
 * @param  direction: 方向控制
 *         0: 停止 (短刹/自由停，代码中实现为两脚置低)
 *         1: 正转
 *         2: 反转
 * @param  pwm_val: PWM占空比值 (速度)，范围建议 0 - 20000 (需匹配定时器ARR值)
 */
void TB6621_B(uint8_t direction, int pwm_val)
{
    // 限制PWM值在安全范围内 (假设最大为2000，根据你的ARR值调整)
    if (pwm_val > 20000) pwm_val = 20000;
		if (pwm_val < 0)  pwm_val = 0;
	
    switch (direction)
    {
        case 0: // 停止 (短刹模式：两个输入都置高，电机快速制动)
            BIN1_L;
            BIN2_L;
            break;
				
        case 1: // 正转
            BIN1_H;
            BIN2_L;
            break;
				
        case 2: // 反转
            BIN1_L;
            BIN2_H;
            break;

        default: // 错误输入，默认停止
            BIN1_H;
            BIN2_H;
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
            break;
    }
		
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, pwm_val);
		
}
