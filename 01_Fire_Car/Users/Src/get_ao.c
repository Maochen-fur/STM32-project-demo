#include "get_ao.h"
#include "oled_hard_i2c.h"


uint32_t adc_value[adc_in_num];



void get_adc_vaule()
{
	for(uint8_t i=0;i < adc_in_num ;i++)
	{
		HAL_ADC_Start(adc_num); 
		if( HAL_ADC_PollForConversion(adc_num, 1) == HAL_OK )
		{
			adc_value[i]= HAL_ADC_GetValue(adc_num);
		}
		else
		{
			if(i<4)
			{
				adc_value[i]=4000;
			}
			else
			{
				adc_value[i]=500;
			}
				
		}
	}
	
}



/**
 * @brief 检查火焰传感器并返回信号最强（数值最小）的有效传感器编号
 * 
 * @return uint8_t 
 *         - 0: 未找到任何有效的火焰信号（所有数据要么超过阈值，要么低于噪声底限）
 *         - 1~4: 对应第1到第4个传感器的编号（表示该传感器检测到了有效且最小的数值）
 */
uint8_t check_fire_min(void)
{
    uint8_t i;
   
    uint32_t min_val = 4096;       
    uint8_t sensor_id = 0;      // 记录最小值对应的传感器编号 (1-4)，0表示无有效数据
    //uint32_t threshold = 3000;  // 火焰检测阈值 (注意：逻辑上取最小值时，阈值的含义可能需要你重新确认)

    // 遍历前4个传感器 (索引 0 到 3)
    uint8_t limit = 4;

    for (i = 0; i < limit; i++)
    {
       
        if ((adc_value[i] < ADC_FIRE_THRESHOLD) && (adc_value[i] > 100))
        {
         
            // 如果当前值比记录的最小值还小，则更新最小值和编号
            if (adc_value[i] < min_val)
            {
                min_val = adc_value[i];
                sensor_id = i + 1; // 转换为 1-4 的编号
            }
        }
    }

    return sensor_id;
}



void OLED_Show_ADC_Value(void)
{
		for(uint8_t i=0;i<adc_in_num;i++)
		{
			 OLED_ShowNum(0,(8*i),adc_value[i],4,8,1);		
		}
	
	
}
	


uint8_t Get_MQ2_value(void)
{
	if( adc_value[4] > 3000)
	{
		return 1;
	}
		
	else
	{
		return 0;
	}
		
}


