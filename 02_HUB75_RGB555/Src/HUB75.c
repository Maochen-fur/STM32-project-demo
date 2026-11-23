#include "HUB75.h"



#define LED_ROW      32
#define LED_COLUMN   64

#define POS_DOWN (LED_COLUMN * LED_ROW / 2)  //预计算下半部分偏移量,下半部分从中间开始
 


//const uint8_t brightness_steps[] = {1,2,4,8,16}; 

const uint8_t brightness_steps[] = {8,16,32,64,128}; 



void led_DRamDis( uint16_t *pdata) {
		
    if(pdata == NULL) return;
    

		for ( uint8_t k = 0; k < 5; k++)
		{
			uint16_t col_depth;
			uint16_t	mask_b = 0x0001 << k;
			uint16_t	mask_g = 0x0020 << k;
			uint16_t	mask_r = 0x0400 << k;

			
			for(uint8_t row = 0; row<16;row++)
			{
				uint16_t *pixel_top = pdata + row * LED_COLUMN;
				uint16_t *pixel_bottom = pixel_top + POS_DOWN;  

				// 1. 设置行地址 - 添加明确的地址线清除
				ADDR_PORT->ODR &= ~(A_PIN | B_PIN | C_PIN | D_PIN);  // 先清除所有地址位
				ADDR_PORT->ODR |=  ((row & 0x01) ? A_PIN : 0) |
													 ((row & 0x02) ? B_PIN : 0) |
													 ((row & 0x04) ? C_PIN : 0) |
													 ((row & 0x08) ? D_PIN : 0);
				

				for(uint16_t j = 0; j < LED_COLUMN; j++) {
					
				 DATA_PORT->ODR = ((pixel_top[j] & mask_b) ? B1_PIN:0)|
													((pixel_top[j] & mask_r) ? R1_PIN:0)|
													((pixel_top[j] & mask_g) ? G1_PIN:0)|
													((pixel_bottom[j] & mask_b) ? B2_PIN:0)|
													((pixel_bottom[j] & mask_r) ? R2_PIN:0)|
													((pixel_bottom[j] & mask_g) ? G2_PIN:0);
						CLK_L;
						CLK_H;
					
						
					
        }

				LAT_L;
        LAT_H;
		
				OE_H;
        OE_L;
				col_depth = brightness_steps[k];
				Delay_us(col_depth);
				OE_H;
				
			}
		}
	
	
	
	
}

 

