#include "esp01s.h"
#include "oled_hard_i2c.h"
#include "delay.h"


uint8_t wifi_buff[255];

FlagStatus  rx_complete_flag = RESET;


void	ESPO1S_Int()
{
	
	if (ESP01S_SendCmd_Printf("OK", "AT\r\n") == SET )
	{
		OLED_ShowString(0,20,(uint8_t *)"AT!AAA",8,1);
	}
	else
	{
		OLED_ShowString(0,20,(uint8_t *)"AT-ERR",8,1);
	}
	
		OLED_Refresh();
	  delay_s(1);
		OLED_Clear();
	
	
		if (ESP01S_SendCmd_Printf("OK", "AT+CIPSTART=\"TCP\",\"bemfa.com\",8344\r\n") == SET )
	{
		OLED_ShowString(0,20,(uint8_t *)"TCP!AAA",8,1);
	}
	else
	{
		OLED_ShowString(0,20,(uint8_t *)"TCP-ERR",8,1);
	}
		OLED_Refresh();
	delay_s(1);
		OLED_Clear();
	
	
		if (ESP01S_SendCmd_Printf("OK", "AT+CIPMODE=1\r\n") == SET )
	{
		OLED_ShowString(0,20,(uint8_t *)"CIP!AAA",8,1);
	}
	else
	{
		OLED_ShowString(0,20,(uint8_t *)"CIP-ERR",8,1);
	}
		OLED_Refresh();
	delay_s(1);
	
		OLED_Clear();
	
	
	if (ESP01S_SendCmd_Printf(">", "AT+CIPSEND\r\n") == SET )
	{
		OLED_ShowString(0,20,(uint8_t *)">!AAA",8,1);
	}
	else
	{
		OLED_ShowString(0,20,(uint8_t *)">-ERR",8,1);
	}
		OLED_Refresh();
	delay_s(1);
	
		OLED_Clear();
	
//	
	if (ESP01S_SendCmd_Printf("res=1", "cmd=1&uid=5ee68f115e634dd59ee4a396b32e5427&topic=DHT11,MQ2,SR04,Lever,MOD\r\n") == SET )
	{
		OLED_ShowString(0,20,(uint8_t *)"uid!AAA",8,1);
	}
	else
	{
		OLED_ShowString(0,20,(uint8_t *)"uid-ERR",8,1);
	}
	
		OLED_Refresh();
	delay_s(1);

		OLED_Clear();

//		ESP01S_SendCmd_Printf("OK", "AT+CIPSTART=\"TCP\",\"bemfa.com\",8344\r\n") ;
//	ESP01S_SendCmd_Printf("OK", "AT+CIPMODE=1\r\n");
//	ESP01S_SendCmd_Printf(">", "AT+CIPSEND\r\n");
//	ESP01S_SendCmd_Printf("res=1", "cmd=1&uid=5ee68f115e634dd59ee4a396b32e5427&topic=DHT11,MQ2,SR04,Lever\r\n") ;
//	ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=Lever&msg=0\r\n");
	
}

void MY_UART_IRQHandler_WIFI()
{
	if(RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))   //判断是否是空闲中断
        {
            __HAL_UART_CLEAR_IDLEFLAG(&huart1);                     //清楚空闲中断标志（否则会一直不断进入中断）
          //  printf("\r\nUART1 Idle IQR Detected\r\n");
          //  USAR_UART_IDLECallback(huart);                          //调用中断处理函数
					
					HAL_UART_DMAStop(&huart1);
					uint8_t data_length  = 255 - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
					if (data_length < 255) 
						{
							wifi_buff[data_length] = '\0';  // 添加字符串结束符
						}	 
					else
						{
							wifi_buff[254] = '\0';  // 留一个位置给结束符
						}

					// **关键：设置接收完成标志**
					rx_complete_flag = SET;  // 告诉主循环数据已收到
//					OLED_Clear();
//					OLED_ShowNum(0,0,data_length,2,8,1);
//					OLED_Refresh();

					HAL_UART_Receive_DMA(&huart1, (uint8_t*)wifi_buff, 255);
        }
	
}


FlagStatus ESP01S_SendCmd_Printf(char *res, char *fmt, ...)
{
	char String[1024];
	uint32_t tick_start;
	rx_complete_flag = RESET;
    va_list arg;
    va_start(arg, fmt);
    vsprintf(String, fmt, arg);
	
		HAL_UART_Transmit(&huart1, (uint8_t*)String, strlen(String), 1000);
		 tick_start = HAL_GetTick();
    while (rx_complete_flag == RESET)
			{
        if ((HAL_GetTick() - tick_start) > 1000) //ms
        {
            return RESET;
        }
			}
		
		if (strstr((const char*)wifi_buff, res) != NULL)
			{
					return SET;  // 成功
			}
			
			return RESET;  // 没找到关键词
	
}
