#include "hc05ble.h"
#include "tb6621.h"
#include "delay.h"
#include "esp01s.h"

uint8_t ble_buff[255];

char dir_cmd = '0' ; // 方向指令 '1'-'9'
char spd_cmd = '0' ; // 速度指令 'A'-'E'
int speed = 0;



	void MY_UART_IRQHandler_BLE()
	{
		if(RESET != __HAL_UART_GET_FLAG(&huart4, UART_FLAG_IDLE))   //判断是否是空闲中断
					{
							__HAL_UART_CLEAR_IDLEFLAG(&huart4);                     //清楚空闲中断标志（否则会一直不断进入中断）
						HAL_UART_DMAStop(&huart4);
						uint8_t data_length  = 255 - __HAL_DMA_GET_COUNTER(&hdma_uart4_rx);
						HAL_UART_Receive_DMA(&huart4, (uint8_t*)ble_buff, 255);
					}
		
	}


	uint8_t Mode_Check(uint8_t mod)
	{
		
				if ( (ble_buff[1] >= 'A' )  && ( ble_buff[1] <= 'E' )) 	//如果收到蓝牙操作
					{

						return 1;		//进入蓝牙操作模式
					}
				else 
					{
						return mod; // 保持原本模式
					}
	}


uint8_t BLE_MOD(uint8_t mod)
{

		dir_cmd = ble_buff[0]; // 方向指令 '1'-'9'
		spd_cmd = ble_buff[1]; // 速度指令 'A'-'E'	检测到 'F' 回到循迹模式
		
		switch (spd_cmd) 
			{
				case 'A': // 左后倒车 (左轮快退，右轮慢退)
						speed = 5000;
						break;

				case 'B': // 后方倒车 (双轮同速反转)
						speed = 10000;
						break;

				case 'C': // 后方倒车 (双轮同速反转)
						speed = 13000;
						break;

				case 'D': // 后方倒车 (双轮同速反转)
						speed = 16000;
						break;

				case 'E': // 后方倒车 (双轮同速反转)
						speed = 19000;
						break;
				case 'F': // 
						mod = 0;
						ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=Lever&msg=0\r\n");
						break;
				default:
						mod = 3 ;
						ESP01S_SendCmd_Printf("res=1", "cmd=2&uid=5ee68f115e634dd59ee4a396b32e5427&topic=Lever&msg=3\r\n");
			}
		
		
		switch (dir_cmd) 
			{
				case '1': // 左后倒车 (左轮快退，右轮慢退)
						TB6621_A(2, speed); // 左轮反转，快
						TB6621_B(2, speed - 5000 ); // 右轮反转，慢
					
						break;

				case '2': // 后方倒车 (双轮同速反转)
						TB6621_A(2, speed);
						TB6621_B(2, speed);
					//	delay_ms(50);
						break;

				case '3': // 右后倒车 (左轮慢退，右轮快退)
						TB6621_A(2, speed - 5000 ); // 左轮反转，慢
						TB6621_B(2, speed); // 右轮反转，快
						
						break;

				case '4': // 原地左转 (左轮反转，右轮正转)
						// 原地旋转通常不需要差速，两边速度一致即可，方向相反
						TB6621_A(2, speed); 
						TB6621_B(1, speed);
					
						break;

				case '5': // 停车
						TB6621_A(0, 0);
						TB6621_B(0, 0);
						
						break;

				case '6': // 原地右转 (左轮正转，右轮反转)
						TB6621_A(1, speed);
						TB6621_B(2, speed);
					
						break;

				case '7': // 左前前进 (左轮慢进，右轮快进) -> 车头向左偏
						TB6621_A(1, speed-5000); // 左轮正转，慢
						TB6621_B(1, speed); // 右轮正转，快
						
						break;

				case '8': // 直行前进 (双轮同速正转)
						TB6621_A(1, speed);
						TB6621_B(1, speed);
						
						break;

				case '9': // 右前前进 (左轮快进，右轮慢进) -> 车头向右偏
						TB6621_A(1, speed); // 左轮正转，快
						TB6621_B(1, speed-5000); // 右轮正转，慢
						
						break;

				default:
						// 收到无效指令，停车或保持原状 (这里选择停车)
						TB6621_A(0, 0);
						TB6621_B(0, 0);
						
						break;
		}
		return mod ;
		
}


