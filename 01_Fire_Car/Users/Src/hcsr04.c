#include "hcsr04.h"



uint32_t startTime = 0;

uint16_t SR04_Get_Distance(void) 
	{

    uint32_t total_distance = 0; // 用于存储总距离
    const int measurements = 3; // 测量次数
 
    for (int i = 0; i < measurements; i++) {
        // 发送 10 us 的高电平信号到 TRIG 引脚
				HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
				delay_us(11); // 确保 TRIG 信号维持至少 10 us
				HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET );
        // 等待 ECHO 引脚变为高电平，开始计时
        while (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_RESET);  
        startTime=0; // 记录开始时间
        // 等待 ECHO 引脚变为低电平，计时结束
        while (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_SET ) 
				{
            // 等待 Echo 引脚低电平结束
					startTime++; 
					delay_us(1);
					if(startTime > 1500)
					{
						 return 222;
					}                           
        }
        uint16_t distance = startTime; // 返回距离（厘米）
        total_distance += distance; // 累加当前测量的距离
				delay_ms(5);
    }
    return (total_distance * 17) / (measurements * 100);

}
